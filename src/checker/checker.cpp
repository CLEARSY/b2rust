/*
   This file is part of b2rust.
   Copyright © CLEARSY 2023
   b2rust is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "checker.h"
#include "../b2rust.h"
#include "../debug.h"
#include "../parser/bxml/assignementsub.h"
#include "../parser/bxml/booleanexp.h"
#include "../parser/bxml/case_sub.h"
#include "../parser/bxml/expcomparison.h"
#include "../parser/bxml/id.h"
#include "../parser/bxml/integerliteral.h"
#include "../parser/bxml/naryexp.h"
#include "../parser/bxml/narypred.h"
#include "../parser/bxml/operation.h"
#include "../parser/bxml/operationcall.h"
#include "../parser/bxml/select.h"
#include "../parser/bxml/varin.h"
#include "../parser/bxml/while.h"
#include "../util/report.h"

bool Checker::checking_error = false;

void Select::checkMe(machineType type, std::unordered_map<std::string, const std::string*>*) {
  // If we are in an implementation, this is forbidden!
  if (type == implementation) {
    Report::emit(Report::Level::ERROR, "SELECT substitution not supported");
    Checker::checking_error = true;
  }
}

void Parser::checkMe() {
  // First, we recursively checks all the imported modules. We take the opportunity to fill a `children` field.
  const Machine* target = (is_base()) ? am : impl;
  if (target->imports) {
    // There are at least one import to check.
    for (const ReferencedMachine* rm : target->imports->referencedMachine) {
      const std::string* rm_name = rm->name;

      // It is necessarily here. In all cases, let’s add it to the children list.
      Parser* import = b2rust::p_imports.at(*rm_name);
      children.insert(import);

      // If it has no already been check, let’s check it and add it to the list of checked `Parser`s.
      auto check = b2rust::c_imports.find(*rm_name);
      if (check == b2rust::c_imports.end()) {
        // Checking has not been done.
        import->checkMe();
        b2rust::c_imports.insert(*rm_name);
      }
    }
  }

  // So, now, `children` contains every imported `Parser` and we can ensure they are checked.

  // Concerning the SETS, we will parse some information into a more relevant shape here.
  // Three things have to be done in order.
  // 1) From children, get the "transmittedSetList" and the "transmittedEnumeratorsModule". This has to be done after recursive
  // translation. 1bis) Translate the enums of the abstract machine. 2) Copy the list from the children, updating them with enums
  // defined inside the abstract machine. 2bis) Translate the enums of the implementation. 3) Copy again the list got from (2)
  // into a private map and a private "set of enums" which also adds the enums used inside the implementation.

  // --- enum 1)
  // std::cout << "We work on machine " << *impl->abstraction << "... " << std::endl;

  for (Parser* child : children) {
    // std::cout << "We work on machine " << *impl->abstraction << "... We are adding st to 'transmittedSetList'; what " <<
    // *child->impl->abstraction << "has." << std::endl; There WON’T BE any clash, if the components are proved. C++23 allows to
    // write only `auto`.
    transmittedSetList.merge(std::unordered_map<std::string, const std::string*>(child->transmittedSetList));
    transmittedEnumeratorsSet.merge(std::unordered_map<std::string, const std::string*>(child->transmittedEnumeratorsSet));
  }

  // --- enum 1bis) and 2)
  // Fills two sets from the infos of a given machine. Used to factorize code...
  static auto workOnSets = [&](const Machine* currentMachine, std::unordered_map<std::string, const std::string*>* setList,
                               std::unordered_map<std::string, const std::string*>* enumeratorsSet, const std::string* abstractMchName) {
    if (currentMachine && currentMachine->sets) {
      for (const Set* set : currentMachine->sets->set) {
        // If it is an enumerated set...
        if (set->enumeratedValues) {
          // std::cout << *impl->abstraction << std::endl;
          if (setList->find(*set->id->value) == setList->end()) {
            setList->insert({*set->id->value, abstractMchName});

            for (const Id* enumerator : set->enumeratedValues->id) {
              enumeratorsSet->insert({*enumerator->value, set->id->value});
            }
          } else {
            Report::emit(Report::Level::ERROR, fmt::format("multiple definition of {} in the type namespace",
							   *set->id->value));
            Checker::checking_error = true;
          }
        }
      }
    }
  };

  workOnSets(am, &transmittedSetList, &transmittedEnumeratorsSet,am->name);

  if (ref) {
    for (auto refinement : *ref) {
      workOnSets(refinement, &transmittedSetList, &transmittedEnumeratorsSet,am->name);
    }
  }

  // --- enum 3)
  // First, we copy the relevant values.
  privateSetList = transmittedSetList;
  privateEnumeratorsSet = transmittedEnumeratorsSet;

  // --- enum 2bis)
  if (impl)
  workOnSets(impl, &privateSetList, &privateEnumeratorsSet,impl->name);

  // Checking of type definition of concrete variables and concrete constants.
  // First, the concrete variables. We need to get them. They can be somewhere among the machine and the implem.
  const std::unordered_set<const std::string*>* parameters = getParametersDeclaration();
  const std::unordered_set<const std::string*>* concreteVariables = getConcreteVariables();

  if (am->invariant) {
    collectTypes(am->invariant->predGroup, &variableTypes, &privateSetList);
  }
  if (ref) {
    for (auto refinement : *ref) {
      if (refinement->invariant) {
        collectTypes(refinement->invariant->predGroup, &variableTypes, &privateSetList);
      }
    }
  }

  if (impl && impl->invariant) {
    collectTypes(impl->invariant->predGroup, &variableTypes, &privateSetList);
  }

  // ------
  // We do the same with the concrete constants.
  const std::unordered_set<const std::string*>* concreteConstants = getConcreteConstants();

  if (am->properties) {
    collectTypes(am->properties->predGroup, &constantTypes, &privateSetList);
  }
  if (ref) {
    for (auto refinement : *ref) {
      if (refinement->properties) {
        collectTypes(refinement->properties->predGroup, &constantTypes, &privateSetList);
      }
    }
  }

  if (impl && impl->properties) {
    collectTypes(impl->properties->predGroup, &constantTypes, &privateSetList);
  }
  checkTypes(parameters, &variableTypes);
  checkTypes(concreteConstants, &constantTypes);
  checkTypes(concreteVariables, &variableTypes);

  // ----------------------
  // We check the instructions of the initialisation.
  if (impl) {
    target->initialisation->sub->checkMe(implementation, &privateSetList);
  } else {
    target->initialisation->sub->checkMe(machine, &privateSetList);
  }
  // ----------------------
  // We check the operations of the abstract machine. It gets the types of input/output parameters, which is quite useful.

  if (am->operations) {
    // There’s at least one operation to oppear on.
    for (Operation* op_spec : am->operations->operations) {
      // We get its implementation. WE SUPPOSE IT EXISTS.
      if (impl && impl->operations) {
        auto it = std::find_if(impl->operations->operations.begin(), impl->operations->operations.end(),
                               [op_spec](Operation* op) { return *op->name == *op_spec->name; });
        // We’ve got it. Now, let’s call the special checker which works on a pair of operations.
        if (it != impl->operations->operations.end())
          checkOperations(op_spec, *it, &privateSetList);

      } else {
        checkOperations(op_spec, NULL, &privateSetList);
      }
    }
  }

  if (impl && impl->localOperations) {
    // There’s at least one operation to oppear on.
    for (Operation* op_spec : impl->localOperations->operations) {
      // We get its implementation. It necessary exist
      auto it = std::find_if(impl->operations->operations.begin(), impl->operations->operations.end(),
                             [op_spec](Operation* op) { return *op->name == *op_spec->name; });
      // We’ve got it. Now, let’s call the special checker which works on a pair of operations.
      checkOperations(op_spec, *it, &privateSetList);
    }
  }
}

void Skip::checkMe(machineType, std::unordered_map<std::string, const std::string*>*) {
  // There’s nothing to check.
}

void NarySub::checkMe(machineType type, std::unordered_map<std::string, const std::string*>* set) {

  if (type == implementation && *op != ";") {
    Report::emit(Report::Level::ERROR, fmt::format("Forbidden substitution {}", *op));
    checking_error = true;
  }
  // Checking the sub instructions.
  for (auto instr : instructions) {
    instr->checkMe(type, set);
  }
}

void VarIn::checkMe(machineType type, std::unordered_map<std::string, const std::string*>* set) {
  // We need to get the list of local variables defined here. We already use the `types` field.
  for (auto id : variables->id) {
    types.insert({*id->value, nullptr});
    // Of course, no type is given. It will be filled later.
  }

  // The error message
  auto message = []() {
    Report::emit(Report::Level::ERROR, "VAR_IN instruction body does not start with local variable typing");
    Checker::checking_error = true;
  };

  // The user has to give at least two subinstructions, i.e. the instruction needs to be a `NarySub`.
  auto ns = dynamic_cast<const NarySub*>(body->sub);
  if (!ns) {
    Report::emit(Report::Level::ERROR, "VAR_IN instruction body has fewer than two instructions.");
    Checker::checking_error = true;
    return;
  }
  auto it = ns->instructions.begin();
  while (std::find_if(types.begin(), types.end(), [](std::pair<std::string, const RustType*> p) { return !p.second; }) != types.end()) {
    // There’s still a variable to search.
    if (it == ns->instructions.end()) {
      // Error: at least one undefined variable.
      Report::emit(Report::Level::ERROR, "Missing typing instructions in VAR_IN instruction body.");
      message();
      return;
    }
    // There’s an instruction.
    const BecomesIn* bi = (*it)->ToBecomesIn();
    if (!bi) {
      message();
      return;
    }
    // The variable name?
    auto _id = bi->variables->id;
    if (_id.size() != 1) {
      Report::emit(Report::Level::ERROR, "BECOMES_IN instruction with list of variables not supported.");
      message();
      return;
    }
    const std::string value = *(*_id.begin())->value;
    auto f = types.find(value);
    if (f == types.end()) {
      // Unknown variable.
      Report::emit(Report::Level::ERROR, fmt::format("BECOMES_IN instruction with unknown variable {}.", value));
      return;
    }
    // It must be not already defined, i.e. `nullptr`.
    if (f->second) {
      Report::emit(Report::Level::ERROR, fmt::format("Multiple typing instructions for variable {}.", value));
      return;
    }
    const RustType* type = bi->value->exp->RightExprType(set);
    if (!type) {
      Report::emit(Report::Level::ERROR, fmt::format("Unrecognized type."));
      return;
    }

    // We can update the `types` `map`!
    f->second = type;

    // print(set);

    // And search for the next instruction.
    ++it;
  }
  // Everything has been checked. The types are correctly defined.
  // `it` now points to: either no instructions (which is useless but possible), either the very first instruction of a list of
  // instructions. It is important to check them (and this will allow the code to throw an error if too many `BecomesIn` are used,
  // for example!).
  for (; it != ns->instructions.end(); ++it) {
    (*it)->checkMe(type, set);
  }
}

void SubstitutionType::checkMe(machineType type, std::unordered_map<std::string, const std::string*>* set) {
  // It falls to the imbricated substitution.
  sub->checkMe(type, set);
}

void BecomesIn::checkMe(machineType type, std::unordered_map<std::string, const std::string*>*) {
  // If the checker is called, it means the `BecomesIn` is not nested in a `VAR_IN` (as the `checkMe` of `VAR_IN` would have skip
  // the `checkMe`s of its first elements).
  if (type == implementation) {
    Report::emit(Report::Level::ERROR, fmt::format("Illegal BECOMES_IN instruction (only allowed at the start of a VAR_IN body)"));
    Checker::checking_error = true;
  };
}

void BecomesSuchThat::checkMe(machineType type, std::unordered_map<std::string, const std::string*>*) {
  // If the checker is called, it means the `BecomesIn` is not nested in a `VAR_IN` (as the `checkMe` of `VAR_IN` would have skip
  // the `checkMe`s of its first elements).
  if (type == implementation) {
    Report::emit(Report::Level::ERROR, fmt::format("Illegal BECOMES_SUCH_THAT instruction (only allowed at the start of a VAR_IN body)"));
    Checker::checking_error = true;
  }
}

void Assertion::checkMe(machineType type, std::unordered_map<std::string, const std::string*>* set) {
  // Not difficult. The checking falls to the nested instruction.
  body->sub->checkMe(type, set);
}

void AssignementSub::checkMe(machineType, std::unordered_map<std::string, const std::string*>*) {
  for (auto expr : variables->exp) {
    expr->checkMe();
  }

  for (auto expr : values->exp) {
    expr->checkMe();
  }
}

void IfSub::checkMe(machineType type, std::unordered_map<std::string, const std::string*>* set) {
  // TODO: the predicate need to be checked!!!!!
  then->checkMe(type, set);
  if (_else)
    _else->checkMe(type, set);
}

void ReferencedMachine::checkMe(machineType, std::unordered_map<std::string, const std::string*>*) const {}

// Default `checkMe(machineType, std::unordered_map<std::string, const std::string*>*)` of a parsed class.
void Parser::checkMe(machineType, std::unordered_map<std::string, const std::string*>*) const {};

void OperationCall::checkMe(machineType, std::unordered_map<std::string, const std::string*>*) {
  // For the implementation, nothing in particular should be respected. Everything is accepted.
}

void Exp::checkMe() const {
  // Nothing by default.
}

void BinaryExp::checkMe() const {

  auto left = exp.at(0);
  auto right = exp.at(1);
  if (*op == "*s") {
    // if left is also a cartesian product  (inv0 * inv1) * inv2) * {ee}
    auto expr = dynamic_cast<const BinaryExp*>(left);
    if (!left->isInterval().has_value()  && !expr) {
      Report::emit(Report::Level::ERROR, "cannot check left argument of cartesian product is an interval");
      Checker::checking_error = true;
      return;
    }

    if (expr && *expr->op == "*s")
      expr->checkBothAreInterval();
  }

  right->checkMe();
  left->checkMe();
}

void BinaryExp::checkBothAreInterval() const {
  auto left = exp.at(0);
  auto right = exp.at(1);
  if (!right->isInterval().has_value() ) {
    Report::emit(Report::Level::ERROR, "cannto check left argument of cartesian product is an interval");
    Checker::checking_error = true;
    return;
  }

  right->checkMe();

  //right is interval, left is interval so far so good
  if (left->isInterval().has_value()){
    return;
  }

  //okay, left is not an interval but maybe it has a bunch of cartesian product
  auto expr = dynamic_cast<const BinaryExp*>(left);
  if (expr && *expr->op == "*s"){
    expr->checkBothAreInterval();
  } else {
    Report::emit(Report::Level::ERROR, "cannot check left argument of cartesian product is an interval");
    Checker::checking_error = true;
  }
}

void NaryExp::checkMe() const {

  auto err = []() {
    Report::emit(Report::Level::ERROR, "illegal expression found (nary expression is not a cartesian product)");
    Checker::checking_error = true;
    return;
  };

  // So, let us verify it has as op "{"
  if (*op != "{") {
    err();
  }

  // alright if its a singleton
  if (exp.size() == 1) {
    exp.at(0)->checkMe();
    return;
  }

  // All its children...
  for (const Exp* e : exp) {
    // ... have to be `BinaryExp`.
    const BinaryExp* be = dynamic_cast<const BinaryExp*>(e);
    if (!be) {
      err();
    }

    // need to be mapplets.
    if (*be->op != "|->") {
      err();
    }

    // The two expressions have to be valid, of course.
    be->exp.at(0)->checkMe();
    be->exp.at(1)->checkMe();

    // The left expression of the mapplet has to be a litteral integer.
    if (!dynamic_cast<const IntegerLiteral*>(be->exp.at(0))) {
      err();
    }
  }

  // Note: every case needs to have an image, but if the program is proven, it is already the case, so, no need to take care of
  // this checking.
}

// The error message
auto message = []() {
  Report::emit(Report::Level::ERROR, "invalid operation precondition");
  Checker::checking_error = true;
};

// Default implementation: does nothing.
void PredGroup::typesListAndCheck(std::unordered_map<std::string, const RustType*>*, std::unordered_map<std::string, const std::string*>*) const {}

void NaryPred::typesListAndCheck(std::unordered_map<std::string, const RustType*>* map,
                                 std::unordered_map<std::string, const std::string*>* sets) const {
  // Allowed only if `&` is used.
  // std::unordered_map<std::string, const RustType *>* map2 = new std::unordered_map<std::string, const RustType *>();
  if (*op == "&") {
    for (const PredGroup* exp : _pred_group) {
      exp->typesListAndCheck(map, sets);
    }
  }
}

void ExpComparison::typesListAndCheck(std::unordered_map<std::string, const RustType*>* map,
                                      std::unordered_map<std::string, const std::string*>* set) const {

  if (exp.size() < 2) {
    return;
  }
  // The left member has to be an `Id`.
  auto left = dynamic_cast<const Id*>(exp.at(0));
  if (!left) {
    return;
  }

  if (*op == ":") {
    const RustType* rt = exp.at(1)->RightExprType(set);
    if (!rt) {
      return;
    }

    // If we are here, it means an interesting type has been found. But we need to throw an error if the found variable has already
    // a `RustType` associated!!
    const std::string varName = *left->value;

    if (map->find(varName) != map->end()) {
      Report::emit(Report::Level::ERROR, fmt::format("multiple typing expressions found for {}.", varName));
      Checker::checking_error = true;
      return;
    }

    // Else, this is fine; we can add the type to the `map`.
    map->insert({varName, rt});
  }
}

void collectTypes(const PredGroup* pg, std::unordered_map<std::string, const RustType*>* types,
                  std::unordered_map<std::string, const std::string*>* set) {
  auto types2 = new std::unordered_map<std::string, const RustType*>();
  if (pg) {
    pg->typesListAndCheck(types2, set);
  }
  for (const auto& entry : *types2) {
    (*types)[entry.first] = entry.second;
  }
  delete types2;
}

void checkTypes(const std::unordered_set<const std::string*>* names, std::unordered_map<std::string, const RustType*>* types) {

  for (const std::string* var : *names) {
    if (types->find(*var) == types->end()) {
      // We found a variable which is not defined inside!!
      Report::emit(Report::Level::WARNING, fmt::format("cannot find type for {}", *var));
      // Checker::checking_error = true;
    }
  }
}

void checkAndGetTypesStrict(const std::unordered_set<const std::string*>* names, const PredGroup* pg,
                            std::unordered_map<std::string, const RustType*>* types, std::unordered_map<std::string, const std::string*>* set) {
  if (pg) {
    pg->typesListAndCheck(types, set);
  }

  // We still need to check everyone was typed, even if there is no `PredGroup`, of course.
  // TODO: it might be useless and we might just need to check the size are the same.
  for (const std::string* var : *names) {
    if (types->find(*var) == types->end()) {
      // We found a variable which is not defined inside!!
      Report::emit(Report::Level::ERROR, fmt::format("cannot find type for {} in MACHINE precondition", *var));
      Checker::checking_error = true;
    }
  }

  // Note: we do not check that there’s no variable typed we do not require to be typed. Hopefully, because `types` might not be
  // empty.
}

void checkOperations(Operation* am, Operation* impl, std::unordered_map<std::string, const std::string*>* sets) {
  // We start by getting the types.

  auto op = new std::unordered_set<const std::string*>;
  if (am->outputParameters) {
    // Get the output parameters.
    for (const Id* id : am->outputParameters->id) {
      op->insert(id->value);
    }
  }
  if (am->inputParameters) {
    for (const Id* id : am->inputParameters->id) {
      op->insert(id->value);
    }
  }

  // In ANY case, we want the field `types` to be initialized.
  am->types = new std::unordered_map<std::string, const RustType*>;
  if (am->precondition) {
    checkAndGetTypesStrict(op, am->precondition->predGroup, am->types, sets);
  } else if (!op->empty()) {
    Report::emit(Report::Level::ERROR, fmt::format("missing precondition for operation {}", *am->name));
    Checker::checking_error = true;
  }

  // Ok; we also put the types in the implementation. It will be very useful.
  if (impl) {
    impl->types = am->types;

    // ---------------
    // Then, we need to check the instructions of the implementation.
    impl->body->sub->checkMe(implementation, sets);
  }

  delete op;
}

void CaseSub::checkMe(machineType type, std::unordered_map<std::string, const std::string*>* sets) {
  value->exp->checkMe();
  choices->checkMe(type, sets);
  if (_else) {
    _else->checkMe(type, sets);
  }
}

void Choices::checkMe(machineType type, std::unordered_map<std::string, const std::string*>* sets) {
  for (auto choice : choices) {
    choice->checkMe(type, sets);
  }
}

void Choice::checkMe(machineType type, std::unordered_map<std::string, const std::string*>* sets) {
  for (size_t i = 0; i < value.size(); i++) {
    value.at(i)->exp->checkMe();
  }
  then->checkMe(type, sets);
}

void BooleanExp::checkMe() const {
  // this->predGroup->checkMe()
}
