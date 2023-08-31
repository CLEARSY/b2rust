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
#include "expcomparison.h"
#include "../bxml/machine.h"
#include "../bxml/id.h"


const PredGroup* _ExpComparison(XMLElement* element) {
  auto ec = new ExpComparison;
  
  attributeActions actions = {{"op", &ec->op}};
  Parser::workOnAttributes(element, &actions, "Error: it seems your input files are not BXML 1.0 compliant.\n");

  workOnElementsVectorExpSpecific<const Exp*>(element, new std::map<std::string, elementAction<const Exp*>>, &ec->exp);

  return ec;
}


const PredGroup* a_ExpComparison(XMLElement* element) {
  auto ec = new ExpComparison;
  
  attributeActions actions = {{"op", &ec->op}};
  Parser::workOnAttributes(element, &actions, Parser::uncompliant);

  // We are only interested in converting `Id`s.
  vectorAction<const Exp*> a_id = {&ec->exp, (const Exp* (*) (XMLElement*)) &_Id};

  Parser::workOnElements<const Attr*, const Exp*>(element, {
      {"Attr", nullopt},
      {"Unary_Exp", nullopt},
      {"Binary_Exp", nullopt},
      {"Ternary_Exp", nullopt},
      {"Nary_Exp", nullopt},
      {"Boolean_Literal", nullopt},
      {"Boolean_Exp", nullopt},
      {"EmptySet", nullopt},
      {"EmptySeq", nullopt},
      {"Id", a_id},
      {"Integer_Literal", nullopt},
      {"Quantified_Exp", nullopt},
      {"Quantified_Set", nullopt},
      {"STRING_Literal", nullopt},
      {"Struct", nullopt},
      {"Record", nullopt},
      {"Real_Literal", nullopt},
      {"Record_Field_Access", nullopt},
    },
    Parser::uncompliant);
  
  return ec;
}
