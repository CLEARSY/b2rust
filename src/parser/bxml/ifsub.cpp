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
#include "ifsub.h"

Sub* _IfSub(XMLElement* element) {
  IfSub* is = new IfSub;

  attributeActions actions = {
    {"elseif", &is->elseif}
  };
  Parser::workOnAttributes(element, &actions, Parser::uncompliant);

  
  simpleAction<const PredicateType*> a_condition = {&is->condition, &_PredicateType};
  simpleAction<SubstitutionType*> a_then = {&is->then, &_SubstitutionType};
  simpleAction<SubstitutionType*> a_else = {&is->_else, &_SubstitutionType};

  Parser::workOnElements<
    const PredicateType*,
    SubstitutionType*
    >(element, {
      {"Condition", a_condition},
      {"Then", a_then},
      {"Else", a_else}
    },
      Parser::uncompliant);

  return is;
}
