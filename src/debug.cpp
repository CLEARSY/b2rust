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
#include <iostream>

#include "debug.h"
#include "./parser/bxml/expcomparison.h"
#include "./parser/bxml/assignementsub.h"
#include "./parser/bxml/integerliteral.h"
#include "./parser/bxml/booleanliteral.h"
#include "./parser/bxml/stringliteral.h"
#include "./parser/bxml/id.h"
#include "./parser/bxml/machine.h"
#include "./parser/bxml/operationcall.h"
#include "./converter/functioncall.h"
#include "./converter/delegatecall.h"
#include "./parser/bxml/unarypred.h"
#include "./parser/bxml/naryexp.h"
#include "./parser/bxml/machine.h"
#include "./parser/bxml/emptyset.h"
#include "./parser/bxml/varin.h"
#include "./parser/bxml/binarypred.h"
#include "./parser/bxml/while.h"
#include "./parser/bxml/narypred.h"
#include "./parser/bxml/type.h"
#include "./converter/arrayaccess.h"
#include "./parser/bxml/booleanexp.h"

using namespace std;



// std::string* printIt(const std::map<std::string, const RustType*>*) {
//   return new std::string("vache");
// }

void Instruction::DebugMe(std::ostream& os) const {
  os << "Old debug function for a `Instruction`!\n";
}

void PredGroup::DebugMe(std::ostream& os) const {
  os << "Old debug function for a `PredGroup`!\n";
}

// For TinyXML2. TODO: it doesn’t work of course (no header). The header cannot be included in other files...
// ostream& operator<<(ostream& os, XMLElement* const element) {
  // os << "It is a XMLElement whose name is " << element->Name() << ".\n";
  // os << "Its attributes are:\n";
  // for (const XMLAttribute* attr = element->FirstAttribute(); attr != NULL; attr = attr->Next()) os << "The attribute " << attr->Name() << " which is " << attr->Value() << std::endl;
//   return os;
// }



void OperationCall::DebugMe(std::ostream& os) const {
  os << debugMe();
}


void EmptySet::DebugMe(std::ostream&) const {
}

ostream& operator<<(ostream& os, std::optional<std::string> o) {
  if (!o) {
    return os << (std::string) "(undefined)\n";
  }
  return os << (std::string) "`" << *o << (std::string) "\n";
}


ostream& operator<<(ostream& os, const Input* const input) {
  os << "The input has parsed the following elements:" << std::endl
     << " – As `include_path`: " << input->project_path << std::endl
     << " – As `main_module_name`: " << input->main_module_name << std::endl
     << " – As `output_directory`: " << input->output_dir << std::endl;
  return os;
}


ostream& operator<<(ostream& os, std::unordered_map<std::string, Module>* map) {
  os << "The following imports were found:\n";
  for (auto const& [key, value] : *map) {
    os << "  – An import of name `" << key;
    os << "`; its module is:\n" << &value;
  }
  return os;
}


ostream& operator<<(ostream& os, const Module* const module) {
  os << "A module; the `XMLElement`s are:\n";
  os << "  — As `am`: " << module->am;
  os << "  — As `impl`: " << module->impl;
  return os;
}




void Skip::DebugMe(std::ostream& os) const {
  os << "A `Skip` instruction";
}


ostream& operator<<(ostream& os, const bool* bl) {
  bl ? (*bl ? os << "true" : os << "false") : os << "(undefined)\n";
  return os;
}



ostream& operator<<(ostream& os, const Printer* const printer) {
  os << "This is a `Printer`; it contains: \n — A path, `" << printer->path << "`;\n – A code stream.\n";
  return os;
}


ostream& operator<<(ostream& os, const exp_type type) {
  switch (type) {
  case Integer_Literal:
    os << "Integer_Literal";
    break;
  case Boolean_Literal:
    os << "Boolean_Literal";
    break;
  default:
    os << "Id";
    break;
  }
  return os;
}



void BinaryExp::DebugMe(std::ostream& os) const {
  os << "A binary expression: the first expression is\n" << exp.at(0) << "..., the symbol is `" << op << "`, the second expression is " << exp.at(1);
}


void IntegerLiteral::DebugMe(std::ostream& os) const {
  os << "An `IntegerLiteral`; it contains:\n";
  os << "[IntegerLiteral 1/3: `attr`:] " << "(not parsed)\n";
  os << "[IntegerLiteral 2/3: `value`:] " << *value << "\n";
  os << "[IntegerLiteral 3/3: `typref`:] " << typref << "\n";
}


void BooleanLiteral::DebugMe(std::ostream& os) const {
  os << "An `BooleanLiteral`; it contains:\n";
  os << "[BooleanLiteral 1/3: `attr`:] " << "(non parsed)\n";
  os << "[BooleanLiteral 2/3: `value`:] " << value;
  os << "[BooleanLiteral 3/3: `typref`:] " << typref;
}

void StringLiteral::DebugMe(std::ostream& os) const {
  os << "An `StringLiteral`; it contains:\n";
  os << "[BooleanLiteral 1/3: `attr`:] " << "(non parsed)\n";
  os << "[BooleanLiteral 2/3: `value`:] " << value;
  os << "[BooleanLiteral 3/3: `typref`:] " << typref;
}

ostream& operator<<(ostream& os, std::map<std::string, RecognizedType> types) {
  for (auto const &[key, value] : types) {
    os << "A predicate for the variable or constant `" << key << "` which tells its type is " << (RecognizedType) value << ".\n";
  }
  return os;
}
ostream& operator<<(ostream& os, const std::map<string, const Exp*>::iterator it) {
  return os << "A values element, whose name is " << it->first << " and which contains the following elements:\n" << it->second;
}


ostream& operator<<(ostream& os, const RecognizedType type) {
  switch (type) {
  case rust_i8:
    return os << "the recognized type `rust_i8`";
    break;
  case rust_i16:
    return os << "the recognized type `rust_i16`";
    break;
  case rust_i32:
    return os << "the recognized type `rust_i32`";
    break;
  case rust_i64:
    return os << "the recognized type `rust_i64`";
    break;
  case rust_i128:
    return os << "the recognized type `rust_i128`";
    break;
  case rust_u128:
    return os << "the recognized type `rust_u128`";
    break;
  case rust_u64:
    return os << "the recognized type `rust_u64`";
    break;
  case rust_u32:
    return os << "the recognized type `rust_u32`";
    break;
  case rust_u16:
    return os << "the recognized type `rust_u16`";
    break;
  case rust_u8:
    return os << "the recognized type `rust_u8`";
    break;
  case rust_bool:
    return os << "the recognized type `rust_bool`";
    break;
  case STRING:
    return os << "the recognized type `STRING`";
    break;
  default:
    return os << "an unrecognized type";
  }
}


void AssignementSub::DebugMe(std::ostream&) const {
  // TODO rewrite this
  // os << "An assignement which assigns this value:\n" << values << "to the variable `" << variable << "`.\n";
}


void IfSub::DebugMe(std::ostream& os) const {
  os << "An `if` instruction whose predicat is the following:\n" << condition << "..., whose `then` clause has the following instructions:\n" << then;
  if (_else == NULL) {
    os << "(No else; end of if.)\n";
  } else {
    os << "... and whose `else` clause has the following instructions:\n" << _else << "(End of if.)\n";
  }
}


ostream& operator<<(std::ostream& os, Instruction* const instruction) {
  if (instruction) {
    instruction->DebugMe(os);
  } else {
    os << "(undefined)\n";
  }
  return os;
}


ostream& operator<<(ostream& os, const Operation* const) {
  // os << "An `Operation`; it contains:\n";
  // os << "[Operation 1/6: `name`:] " << op->name;
  // os << "[Operation 2/6: `attr`:] " << op->attr;
  // os << "[Operation 3/6: `precondition`:] " << op->precondition;
  // os << "[Operation 4/6: `outputParameters`:] " << op->outputParameters;
  // os << "[Operation 5/6: `inputParameters`:] " << op->inputParameters;
  // os << "[Operation 6/6: `body`:] " << op->body;

  // // OLD CODE
  // os << "operation of name " << op->name << ", which has the following output parameters: ";
  // for (std::string outp : op->output_parameters) {
  //   os << "`" << outp << "`, ";
  // }
  // os << ", wh";
  // // os << "and which does the following instruction:\n" << op->instruction;
  return os;
}


// ---------------------------------------------- CONVERTER


ostream& operator<<(ostream& os, const RustModule* const md) {
  os << "\033[1mA `RustModule`, whose name is `" << md->name << "`, which contains the following elements:\033[0m\n";
  if (!md->mods.empty()) {
    os << "  – A `mod`s set; it contains:\n";
    for (auto s : md->mods) {
      os << "    – " << s;
    }
  }

  if (!md->uses.empty()) {
    os << "  – A `use`s set; it contains:\n";
    for (auto s : md->uses) {
      os << "    – " << s;
    }
  }

  // const std::map<std::string, RecognizedType> variables;
  for (auto const &[key, value] : md->variables) os << "A variable definition; its name is `" << key << "` and its type is `" << value->PrintMe() << "`.\n";
  os <<	"\033[1mAn initialisation, which contains the following instructions:\033[0m\n" << &md->initialisations;
  for (const Function* function : md->functions) os << function;
  return os;
}


void RustAssignement::DebugMe(std::ostream&) const {
  // os << "An assignement; it sets the value of the `" << variable << "` variable to the following expression:\n" << expression;
}


ostream& operator<<(ostream& os, const comparisonSymbol symbol) {
  static const std::map<comparisonSymbol, std::string> assoc = {
    {comparisonSymbol::LessThan, "is less than"},
    {comparisonSymbol::LessThanOrEqualTo, "is less than or equal to"},
    {comparisonSymbol::EqualTo, "is equal to"},
    {comparisonSymbol::MoreThanOrEqualTo, "is more than or equal to"},
    {comparisonSymbol::MoreThan, "is more than"},

    {comparisonSymbol::NotEqualTo, "is not equal to"},
    {comparisonSymbol::And, "has a logical and with"},
    {comparisonSymbol::Or, "has a logical or with"}
  };
  return os << assoc.at(symbol);
}


void RustIf::DebugMe(std::ostream& os) const {
  os << "An `if` instruction whose condition is the following:\n" << predicate << "..., whose `then` clause has the following instructions:\n" << then_instr << "... and whose `else` clause has the following instructions:\n" << else_instr;;
}


ostream& operator<<(ostream& os, const std::vector<const RustInstruction*>* instructions) {
  for (const RustInstruction* instruction : *instructions) instruction->DebugMe(os);
  return os;
}


ostream& operator<<(ostream& os, const Function* const f) {
  os << "  A function with the name " << f->name << ". ";
  if (f->outputParameters.empty()) {
    os << "It has no output parameters, ";
  } else {
    os << "Its output parameters are: ";
    for (auto param : f->outputParameters) {
      os << "`" << param.first << "` (of type `";
      param.second->DebugMe(os);
      os << "`), ";
    }
  }
  os << "and it has the following instructions:\n";
  os << &f->instructions;
  return os;
}


ostream& operator<<(ostream& os, const RustExpression* const expression) {
  os << "An expression whose Rust type will be " << "type" << " and whose value, in C++, is " << expression->PrintMe() << ".\n";
  return os;
}


void ExpComparison::DebugMe(std::ostream& os) const {
  // Caution: especially in an abstract machine, an `ExpComparison` could contain not exactly two expressions. In this case, it is ill-formed.
  if (exp.size() != 2) {
    os << "An illformed `ExpComparison` ";
    if (exp.size() == 1) {
      os << "(it has only one expression which is:\n" << exp.at(0);
      os << ").\n";
    } else if (exp.size() == 0) {
      os << "(it doesn’t contain any expression).\n";
    }
  } else {
    os << "An ExpComparison which says the expression:\n" << exp.at(0) << "... is compared with the symbol:\n" << op << "... with the expression:\n" << exp.at(1) << ".\n";
  }
}


ostream& operator<<(ostream& os, const PredGroup* const predicate) {
  predicate->DebugMe(os);
  return os;
}


void RustBinaryPredicate::DebugMe(std::ostream& os) const {
  os << "An RustBinaryPredicate which says the expression:\n" << left_expr << "... is compared with the symbol:\n" << symbol << "... with the expression:\n" << right_expr;
}


ostream& operator<<(ostream& os, const RustPredicate* const predicate) {
  predicate->DebugMe(os);
  return os;
}


void NaryPred::DebugMe(std::ostream&) const {
  // os << "A Nary_Pred which has the symbol " << op;
  // if (_pred_group.empty()) os << " and which includes no predicate.\n";
  // else {
  //   os << " and which includes the following predicates:\n";
  //   for (const PredGroup* predicate : _pred_group) {
  //     os << "  – ";
  //     predicate->DebugMe(os);
  //   }
  // }
  // os << "(End of Nary_Pred.)\n";
}


void RustPredicateAggregate::DebugMe(std::ostream& os) const {
  os << "An RustPredicateAggregate which whose symbol used is " << symbol << "and whose predicates are:\n";
  for (const RustPredicate* predicate : *predicates) {
    predicate->DebugMe(os);
  }
  os << "(End of RustPredicateAggregate.)\n";
}


void UnaryPred::DebugMe(std::ostream&) const {
  // os << "An Unary_Pred with the symbol " << op << " and the following subpredicate:\n";
  // _pred_group->DebugMe(os);
}


void RustUnaryPredicate::DebugMe(std::ostream& os) const {
  os << "A RustUnaryPredicate with a certain symbol and the following subpredicate:\n";
  predicate->DebugMe(os);
}


void Assertion::DebugMe(std::ostream& os) const {
  os << "An assertion which contains the following assertion:\n";
  guard->DebugMe(os);
  os << "... and which concerns the following instruction:\n";
  body->DebugMe(os);
}


void VarIn::DebugMe(std::ostream&) const {
  // os << "A VAR_IN instruction, which declares the following variables: " << variables << "and which contains the following instruction:\n" << instruction << "(End of VAR_IN.)\n";
}


ostream& operator<<(ostream& os, std::set<std::string> set) {
  for (std::string str : set) {
    os << "`" << str << "`, ";
  }
  return os;
}


void Int::DebugMe(ostream& os) const {
  os << "An integer of value " << value << ".\n";
}




void Bool::DebugMe(ostream& os) const {
  os << "A boolean of value " << value << ".\n";
}

void RustString::DebugMe(ostream& os) const {
  os << "A string of value " << value << ".\n";
}


void GlobalVariable::DebugMe(ostream& os) const {
  os << "A global variable, " << name << ".\n";
}

void GlobalConstant::DebugMe(ostream& os) const {
  os << "A global constant, " << name << ".\n";
}

void LocalVariable::DebugMe(ostream& os) const {
  os << "A local variable, " << name << ".\n";
}

void UnknownVariable::DebugMe(ostream& os) const {
  os << "An untyped variable, " << name << ".\n";
}

void ParameterVariable::DebugMe(ostream& os) const {
  os << "A parameter variable, " << name << ".\n";
}

void FieldAccess::DebugMe(ostream& os) const {
  os << "A field access , " << name << ".\n";
}

void ConstantAccess::DebugMe(ostream& os) const {
  os << "A CONSTANT access , " << name << ".\n";
}


void BinaryRustExpression::DebugMe(ostream& os) const {
  os << "A binary expression which is " << type << " between the expression:\n" << left_expr << "... and the expression:\n" << right_expr << "(End of binary expression.)\n";
}


ostream& operator<<(ostream& os, binaryExpression exp) {
  switch (exp) {
  case addition:
    os << "an addition";
    break;
  case substraction:
    os << "a substraction";
    break;
  case multiplication:
    os << "a multiplication";
    break;
  case division:
    os << "a division";
    break;
  case exponentiation:
    os << "an exponentiation";
    break;
  default:
    os << "a modulo";
    break;
  }

  return os;
}


void NarySub::DebugMe(std::ostream& os) const {
  os << "A Nary_Sub; its op is `" << op << "` and its instructions are the following:\n" << &instructions << "(End of Nary_Sub.)\n";
}


ostream& operator<<(ostream& os, const std::vector<Instruction*>* instructions) {
  for (Instruction* instruction : *instructions) {
    os << instruction;
  }
  return os;
}

void Block::DebugMe(std::ostream& os) const {
  os << "A block of Rust instructions; it contains the following instructions:\n" << instructions << "(End of Block.)\n";
}


void SubstitutionType::DebugMe(std::ostream&) const {
  // os << "A `SubstitutionType`; it contains the following instruction:\n" << _sub;
}


void PredicateType::DebugMe(std::ostream&) const {
  // os << "A `PredicateType`; it contains the following predicate:\n" << _pred_group;
}

void RustArray::DebugMe(std::ostream&) const {
}

void NaryExp::DebugMe(std::ostream&) const {
}


ostream& operator<<(ostream& os, std::map<const std::string, const RustType*>* types) {
  os << "A set of variables names associated to types; there is:\n";
  for (auto def : *types) {
    os << "— A definition for the variable `" << def.first << "`; its type is `";
    def.second->DebugMe(os);
    os << "`;\n";
  }
  return os;
}


void bool_t::DebugMe(std::ostream& os) const {
  os << "bool_t";
}

void i8_t::DebugMe(std::ostream& os) const {
  os << "i8_t";
}

void i16_t::DebugMe(std::ostream& os) const {
  os << "i16_t";
}

void i32_t::DebugMe(std::ostream& os) const {
  os << "i32_t";
}

void i64_t::DebugMe(std::ostream& os) const {
  os << "i-4_t";
}

void i128_t::DebugMe(std::ostream& os) const {
  os << "i128_t";
}

void u8_t::DebugMe(std::ostream& os) const {
  os << "u8_t";
}

void u16_t::DebugMe(std::ostream& os) const {
  os << "u16_t";
}

void u32_t::DebugMe(std::ostream& os) const {
  os << "u32_t";
}

void u64_t::DebugMe(std::ostream& os) const {
  os << "u64_t";
}


void u128_t::DebugMe(std::ostream& os) const {
  os << "u128_t";
}


void string_t::DebugMe(std::ostream& os) const {
  os << "string_t";
}

ostream& operator<<(ostream& os, const std::set<std::string>* set) {
  os << "A set of strings; there is:\n";
  for (auto name : *set) {
    os << "— `" << name << "`;\n";
  }
  return os;
}


void Declaration::DebugMe(std::ostream& os) const {
  os << "A variable declaration; the variable’s declared name is `" << *name << "` and its type is `";
  type->DebugMe(os);
  os << "`.\n";
}


ostream& operator<<(ostream& os, const VariablesType*) {
  // if (vtypes) {
  //   os << "A `VariablesType`; it contains:\n";
  //   os << "— An attribute `_attr`: " << vtypes->_attr;
  //   os << "— An attribute `_id`: ";
  //   os << (std::vector<const Id*>*) &vtypes->_id;
  // } else {
  //   os << "(undefined)\n";
  // }
  return os;
}


ostream& operator<<(ostream& os, const Attr* attr) {
  if (attr == nullptr) {
    os << "(undefined)\n";
  } else {
    os << "An `Attr`.\n";
  }
  return os;
}


void Id::DebugMe(std::ostream& os) const {
  os << "An `Id`; it contains:\n";
  os << "— An attribute `_attr`: " << "(non parsed)\n";
  os << "— An attribute `value`: " << value;
  os << "— An attribute `suffix`: " << suffix;
  os << "— An attribute `typref`: " << typref << "\n";
}


ostream& operator<<(ostream& os, std::vector<const Id*>* v) {
  os << "A vector of `Id`s; it contains:\n";
  for (auto id : *v) {
    id->DebugMe(os);
  }
  return os;
}


ostream& operator<<(ostream& os, const unsigned* s) {
  if (s == nullptr) {
    os << "(undefined)\n";
  } else {
    os << *s;
  }
  return os;
}


ostream& operator<<(ostream& os, const int* i) {
  if (i == nullptr) {
    os << "(undefined)\n";
  } else {
    os << *i;
  }
  return os;
}


std::ostream& operator<<(std::ostream& os, const ExpressionType* et) {
  os << "An `ExpressionType`; it contains the following elements:\n" << et->exp;
  return os;
}


std::ostream& operator<<(std::ostream& os, const Exp* exp) {
  if (exp == nullptr) {
    os << "(undefined)\n";
  } else {
    exp->DebugMe(os);
  }
  return os;
}


void BecomesIn::DebugMe(std::ostream& os) const {
  os << "A `BecomesIn` instruction; it contains:\n";
  os << "[BecomesIn 1/3] An attribute `_attr`: " << _attr;
  os << "[BecomesIn 2/3] An attribute `variables`: " << variables;
  os << "[BecomesIn 3/3] An attribute `value`: " << value;
  os << "(End of `BecomesIn`.)\n";
}


void BecomesSuchThat::DebugMe(std::ostream& os) const {
    os << "A `BecomesSuchThat` instruction; it contains:\n";
  os << "[BecomesSuchThat 1/3] An attribute `_attr`: " << _attr;
  os << "[BecomesSuchThat 2/3] An attribute `variables`: " << variables;
  pred->DebugMe(os);
  os << "(End of `BecomesSuchThat`.)\n";
}


ostream& operator<<(ostream& os, const Operations* operations) {
  if (operations) {
    os << "An `Operations`; it contains:\n";
    os << "[Operations 1/2: `attr`:] " << operations->attr;
    os << "[Operations 2/2: vector `operations`:]\n";
    for (const Operation* operation : operations->operations) {
      os << "  – " << operation;
    }
    os << "(End of `Operations`.)\n";
  } else {
    os << "(undefined)\n";
  }

  return os;
}


ostream& operator<<(ostream& os, const Invariant* inv) {
  if (inv) {
    os << "An `Invariant` (or `Invariant`...); it contains:\n";
    // os << "[`Invariant` 1/2: `attr`:] " << inv->attr;
    os << "[`Invariant` 2/2: `predGroup`:] " << inv->predGroup;
  } else {
    os << "(undefined)\n";
  }

  return os;
};


ostream& operator<<(ostream& os, const Id* id) {
  id->DebugMe(os);
  return os;
}


std::ostream& operator<<(std::ostream& os, const InstanceListType* ilt) {
  if (!ilt) return os << "(undefined)\n";
  os << "An `InstanceListType`; it contains:\n";
  os << "  – A vector of `ReferencedMachine`; it contains:\n";
  for (auto r : ilt->referencedMachine) {
    os << r;
  }
  return os;
}


std::ostream& operator<<(std::ostream& os, const ReferencedMachine* rm) {
  os << "A `ReferencedMachine`; it contains:\n";
  os << "  — As `name`: " << rm->name;
  os << "  — As `instance`: " << rm->instance;
  return os;
}



// --------------------------------------- TOOLS

std::string* indentMe(const std::string* string) {
  std::string* corrected = new std::string;
  std::size_t oldPosition = 0;
  std::size_t last_occurrence = string->length()-1;
  std::size_t position;
  while (true) {
    position = string->find("\n", oldPosition);
    corrected->append(*string, oldPosition, position-oldPosition);
    // 1: size of "\n". We don’t want to change the last occurrence.
    if (position == last_occurrence) break;
    // There’s a match to change from position `position`.
    *corrected += "\n  ";
    // 1: size of "\n".
    oldPosition = position+1;
  }
  *corrected += "\n";
  return corrected;
}


std::string* printIt(const std::string* object) {
  if (!object) return new std::string("(Undefined.)\n");
  return indentMe(printIt(*object));
}


std::string* printIt(const cpp_int object) {
  if (!object) return new std::string("(Undefined.)\n");
  return indentMe(new std::string("( cpp_int) " + object.str()+"\n"));
}


std::string* printIt(const cpp_int* object) {
  if (!object) return new std::string("(Undefined.)\n");
  return indentMe(printIt(*object));
}


std::string* printIt(const std::string object) {
  return indentMe(new std::string("(std::string) "+object + "\n"));
}


std::string* printIt(const int* object) {
  if (!object) return new std::string("(Undefined.)\n");
  return indentMe(new std::string("(int) "+std::to_string(*object)+"\n"));
}


std::string* printIt(const unsigned int* object) {
  if (!object) return new std::string("(Undefined.)\n");
  return indentMe(new std::string("(unsigned int) "+std::to_string(*object)+"\n"));
}


// ---------------------------------------

// --- ABSTRACTION ---
std::string* Abstraction::debugMe() const {
  std::string* output = new std::string;
  *output += "An `Abstraction`; it is an alias for `std::string` and its value is `"+*printIt(&_);
  return output;
}

// --- BINARYPRED ---
std::string* BinaryPred::debugMe() const {
  std::string* output = new std::string;
  *output += "A `BinaryPred`; to implement!\n";
  return output;
}

// --- CONTEXT ---
std::string* Context::debugMe() const {
  std::string* output = new std::string;
  *output += "A `Context`; it contains:\n";
  *output += "  – As `parameters`:\n    " + *printIt(&parameters);
  *output += "  – As `global`:\n    " + *printIt(&globalVariables);
  *output += "  – As `instancesNameAssoc`:\n    " + *printIt(&instancesNameAssoc);
  *output += "  – As `operationNameAssoc`:\n    " + *printIt(&operationNameAssoc);
  return output;
}

// --- ENUMERATEDVALUES ---
std::string* EnumeratedValues::debugMe() const {
  std::string* output = new std::string;
  *output += "An `EnumeratedValues`; it contains:\n";
  // *output += "  – As `operationNameAssoc`:\n    " + *printIt(&operationNameAssoc);
  return output;
}

// --- EXPCOMPARISON ---
std::string* ExpComparison::debugMe() const {
  std::string* output = new std::string;
  *output += "An `ExpComparison`; it contains:\n";
  // *output += "  – As `operationNameAssoc`:\n    " + *printIt(&operationNameAssoc);
  return output;
}

// --- FUNCTION_CALL ---
std::string* FunctionCall::debugMe() const {
  std::string* output = new std::string;
  *output += "A `FunctionCall`; it contains:\n";
  *output += "  – As `moduleName`: \n    " + *printIt(&moduleName);
 // *output += "  – As `functionName`: \n    " + *printIt(&function);
  *output += "  – As `inputParameters`: \n    " + *printIt(&inputParameters);
  *output += "  – As `outputParameters`: \n    " + *printIt(&outputParameters);
  return output;
}

std::string* DelegateCall::debugMe() const {
  std::string* output = new std::string;
  *output += "A `FunctionCall`; it contains:\n";
  *output += "  – As `moduleName`: \n    " + *printIt(&moduleName);
  *output += "  – As `functionName`: \n    " + *printIt(&functionName);
  *output += "  – As `inputParameters`: \n    " + *printIt(&inputParameters);
  *output += "  – As `outputParameters`: \n    " + *printIt(&outputParameters);
  return output;
}

// --- ID ---
std::string* Id::debugMe() const {
  std::string* output = new std::string;
  *output += "An `Id`; it contains:\n";
  *output += "  – As `value`: \n    " + *printIt(value);
  *output += "  – As `suffix`: \n    " + *printIt(suffix);
  *output += "  – As `typref`: \n    " + *printIt(typref);
  return output;
}

// --- INSTANCELISTTYPE ---
std::string* InstanceListType::debugMe() const {
  std::string* output = new std::string;
  *output += "An `InstanceListType`; it contains:\n";
  *output += "  – As `referencedMachine`: \n    " + *printIt(&referencedMachine);
  return output;
}

// --- INVARIANT ---
std::string* Invariant::debugMe() const {
  std::string* output = new std::string;
  *output += "An `Invariant`; to implement!:\n";
  // *output += "  – As `operationNameAssoc`:\n    " + *printIt(&operationNameAssoc);
  return output;
}

// --- MACHINE ---
std::string* Machine::debugMe() const {
  std::string* output = new std::string;
  *output += "A `Machine`; it contains:\n";
  *output += "  – As `abstraction`: \n    " + *printIt(abstraction);
  *output += "  – As `imports`: \n    " + *printIt(imports);
  *output += "  – As `values`: \n    " + *printIt(values);
  *output += "  – As `sets`: \n    " + *printIt(sets);
  *output += "  – As `abstractConstants`: \n    " + *printIt(abstractConstants);
  *output += "  – As `concreteConstants`: \n    " + *printIt(concreteConstants);
  *output += "  – As `abstractVariables`: \n    " + *printIt(abstractVariables);
  *output += "  – As `concreteVariables`: \n    " + *printIt(concreteVariables);
  *output += "  – As `properties`: \n    " + *printIt(properties);
  *output += "  – As `invariant`: \n    " + *printIt(invariant);
  *output += "  – As `initialisation`: \n    " + *printIt(initialisation);
  *output += "  – As `operations`: \n    " + *printIt(operations);
  return output;
}

// --- NARYPRED ---
std::string* NaryPred::debugMe() const {
  std::string* output = new std::string;
  *output += "A `NaryPred`; to implement!:\n";
  // *output += "  – As `abstraction`: \n    " + *printIt(abstraction);
  return output;
}

// --- OPERATIONCALL ---
std::string* OperationCall::debugMe() const {
  std::string* output = new std::string;
  *output += "An `OperationCall`; it contains:\n";
  *output += "  – As `name`:\n    "+*printIt(name);
  *output += "  – As `inputParameters`:\n    "+*printIt(inputParameters);
  *output += "  – As `outputParameters`:\n    "+*printIt(outputParameters);
  return output;
}

// --- OPERATIONCALLNAME ---
std::string* OperationCall_Name::debugMe() const {
  std::string* output = new std::string;
  *output += "An `OperationCall_Name`; it contains:\n";
  *output += "  – As `id`: " + *printIt(id);
  return output;
}

// --- OPERATIONCALLNAMEID ---
std::string* OperationCall_Name_Id::debugMe() const {
  std::string* output = new std::string;
  *output += "An `OperationCall_Name_Id`; it contains:\n";
  *output += "  – As `value`: " + *printIt(value);
  *output += "  – As `instance`: " + *printIt(instance);
  *output += "  – As `component`: " + *printIt(component);
  return output;
}

// --- OPERATIONS ---
std::string* Operations::debugMe() const {
  std::string* output = new std::string;
  *output += "An `Operations`; it contains:\n";
  *output += "  to implement!\n";
  return output;
}

// --- PARSER ---
std::string* Parser::debugMe() const {
  std::string* output = new std::string;
  *output += "An `Parser`; it contains:\n(To implement)\n";
  return output;
}

// --- PREDICATETYPE ---
std::string* PredicateType::debugMe() const {
  std::string* output = new std::string;
  *output += "A `PredicateType`; it contains:\n";
  *output += "  — As `pred_group`: " + *printIt(pred_group);
  return output;
}

// --- REFERENCEDMACHINE ---
std::string* ReferencedMachine::debugMe() const {
  std::string* output = new std::string;
  *output += "A `ReferencedMachine`; (to implement)\n";
  return output;
}

// --- RUSTEXPRESSION ---
std::string* RustExpression::debugMe() const {
  std::string* output = new std::string;
  *output += "A `RustExpression`; (to implement)\n";
  return output;
}

// --- RUSTMODULE ---
std::string* RustModule::debugMe() const {
  std::string* output = new std::string;
  *output += "A `RustModule`; it contains:\n";
  // *output += "  — As `parser`: " + *printIt(parser);
  // *output += "  — As `am`: " + *printIt(am);
  // *output += "  — As `impl`: " + *printIt(impl);
  *output += "  — As `name`: " + *printIt(name);
  *output += "  — As `children`: " + *printIt(&children);
  *output += "  — To implement!\n";
  return output;
}

// --- RUSTTYPE ---
std::string* RustType::debugMe() const {
  std::string* output = new std::string;
  *output += "A `RustType`; (to implement)\n";
  return output;
}

// --- SET ---
std::string* Set::debugMe() const {
  std::string* output = new std::string;
  *output += "A `Set`; to implement!:\n";
  // *output += "  – As `abstraction`: \n    " + *printIt(abstraction);
  return output;
}

// --- SETS ---
std::string* Sets::debugMe() const {
  std::string* output = new std::string;
  *output += "A `Sets`; to implement!:\n";
  // *output += "  – As `abstraction`: \n    " + *printIt(abstraction);
  return output;
}

// --- TYPEBINARYEXP ---
std::string* Type_BinaryExp::debugMe() const {
  std::string* output = new std::string;
  *output += "A `Type_BinaryExp`; (to implement)\n";
  return output;
}

// --- TYPEGENERICTYPE ---
std::string* Type_GenericType::debugMe() const {
  std::string* output = new std::string;
  *output += "A `Type_GenericType`; (to implement)\n";
  return output;
}

// --- TYPEID ---
std::string* Type_Id::debugMe() const {
  std::string* output = new std::string;
  *output += "A `Type_Id`; (to implement)\n";
  return output;
}

// --- TYPEINFOS ---
std::string* TypeInfos::debugMe() const {
  std::string* output = new std::string;
  *output += "A `TypeInfos`; (to implement)\n";
  return output;
}

// --- TYPEINFOSTYPE ---
std::string* TypeInfosType::debugMe() const {
  std::string* output = new std::string;
  *output += "A `TypeInfosType`; (to implement)\n";
  return output;
}

// --- TYPESTRUCT ---
std::string* Type_Struct::debugMe() const {
  std::string* output = new std::string;
  *output += "A `Type_Struct`; (to implement)\n";
  return output;
}

// --- TYPESTRUCTRECORDITEM ---
std::string* Type_Struct_RecordItem::debugMe() const {
  std::string* output = new std::string;
  *output += "A `Type_Struct_RecordItem`; (to implement)\n";
  return output;
}

// --- TYPEUNARYEXP ---
std::string* Type_UnaryExp::debugMe() const {
  std::string* output = new std::string;
  *output += "A `Type_UnaryExp`; (to implement)\n";
  return output;
}

// --- UNARYPRED ---
std::string* UnaryPred::debugMe() const {
  std::string* output = new std::string;
  *output += "An `UnaryPred`; to implement!:\n";
  // *output += "  – As `abstraction`: \n    " + *printIt(abstraction);
  return output;
}

// --- VARIABLESTYPE ---
std::string* VariablesType::debugMe() const {
  std::string* output = new std::string;
  *output += "An `VariablesType`; it contains:\n    ";
  *output += "— A vector of `Id`; " + *indentMe(printIt(&id));
  return output;
}

// --- WHILE ---
std::string* While::debugMe() const {
  std::string* output = new std::string;
  *output += "A `While`; to implement!:\n";
  return output;
}

// --- __EXPVECTOR ---
std::string* __ExpVector::debugMe() const {
  std::string* output = new std::string;
  *output += "A `__ExpVector`; it contains:\n";
  *output += "  – As `exp`: a vector of `Exp` which contain the following elements:\n";
  std::stringstream ss;
  for (auto i_exp : exp) {
    i_exp->DebugMe(ss);
  }
  std::stringstream sss;
  sss << ss.rdbuf();
  std::string str = sss.str();
  *output += "    " + *indentMe(&str) + "\n";

  return output;
}


// --- __IDVECTOR ---
std::string* __IdVector::debugMe() const {
  std::string* output = new std::string;
  *output += "A `__IdVector`; it contains:\n";
  *output += "  – As `id`: a vector of `Id` which contain the following elements:\n";
  std::stringstream ss;
  for (auto i_id : id) {
    i_id->DebugMe(ss);
  }
  std::stringstream sss;
  sss << ss.rdbuf();
  std::string str = sss.str();
  *output += "    " + *indentMe(&str) + "\n";

  return output;
}



void Match::DebugMe(std::ostream& os) const {
  os << "A match instruction which compare the expression " << target << " with ";
  for (size_t i = 0; i < cases -> size(); i++){
    cases -> at(i) -> DebugMe(os);
  }

  if (_default != NULL){
    _default -> DebugMe(os);
  }


};


void RustCase::DebugMe(std::ostream& os) const {
  os << "[Case]" << " : " ;

  for (size_t i = 0; i<value->size(); i++){
    value->at(i) -> DebugMe(os);
  }
  os << " => ";
  then -> DebugMe(os);
}


void RustUniformArray::DebugMe(std::ostream& os) const {
    os << "[tab]" << " : " ;
    size -> DebugMe(os);
    os << ";";
    value -> DebugMe(os);
};

void ArrayAccess::DebugMe(std::ostream& os) const {
    this->array->DebugMe(os);
    os << "[indexes]" << " : " ;
    for (size_t i = 0; i<indexes.size(); i++){
     indexes.at(i) -> DebugMe(os);
    }
};


void IntegerType::DebugMe(std::ostream& os) const {
  os << "integertype should never be triggered";

};

void ErrorType::DebugMe(std::ostream& os) const {
os << "errortype should never be triggered";
};

void BooleanExp::DebugMe(std::ostream& os) const{
  this->predGroup->DebugMe(os);
}