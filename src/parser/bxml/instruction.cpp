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
#include "instruction.h"
#include "operation.h"
#include "skip.h"
#include "expcomparison.h"
#include "expressiontype.h"

const NarySub* Instruction::ToNarySub() const {
  // By default, an instruction is not a `NarySub`...
  return NULL;
}
const BecomesIn* Instruction::ToBecomesIn() const {
  return NULL;
}





Instruction* _BecomesIn(XMLElement* element) {
  BecomesIn* bi = new BecomesIn;

  simpleAction<const Attr*> a_attr = {&bi->_attr, &_Attr};
  simpleAction<const VariablesType*> a_variables = {&bi->variables, &_VariablesType};
  simpleAction<const ExpressionType*> a_value = {&bi->value, &_ExpressionType};

  Parser::workOnElements<const Attr*, const VariablesType*, const ExpressionType*>(element, {
      {"Attr", a_attr},
      {"Variables", a_variables},
      {"Value", a_value}
    }, "Error: it seems your input files are not BXML 1.0 compliant.\n");

  return bi;
}

Instruction* _BecomesSuchThat(XMLElement* element) {
  BecomesSuchThat* bst = new BecomesSuchThat;

  simpleAction<const Attr*> a_attr = {&bst->_attr, &_Attr};
  simpleAction<const VariablesType*> a_variables = {&bst->variables, &_VariablesType};
  simpleAction<const PredicateType*> a_pred = {&bst->pred, &_PredicateType};

  Parser::workOnElements<const Attr*, const VariablesType*, const PredicateType*>(element, {
      {"Attr", a_attr},
      {"Variables", a_variables},
      {"Pred", a_pred}
    }, "Error: it seems your input files are not BXML 1.0 compliant.\n");

  return bst;
}

const BecomesIn* BecomesIn::ToBecomesIn() const {
  return this;
}

const BecomesIn* BecomesSuchThat::ToBecomesIn() const{
  auto bi = new BecomesIn;
  bi->variables = variables;
  bi->value = new ExpressionType;
  auto ec = dynamic_cast<const ExpComparison*>(pred->pred_group);
  if(ec && *ec->op == ":" && ec->exp.size() == 2){
    auto& ptr = const_cast<Exp*&>((bi->value->exp));
    ptr = const_cast<Exp *> (ec->exp.at(1)); 
  } 
  return bi;
}



// We put the `ConvertMe` of the `Skip` here, because it is quite short...
void Skip::ConvertMe(const Context*, std::vector<const RustInstruction*>*) const {
};
