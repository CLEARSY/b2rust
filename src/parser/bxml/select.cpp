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
#include "select.h"


const Select_When* _Select_When(tinyxml2::XMLElement* element) {
  auto sw = new Select_When;

  simpleAction<const PredicateType*> a_condition = {&sw->condition, &_PredicateType};
  simpleAction<SubstitutionType*> a_then = {&sw->then, &_SubstitutionType};
  Parser::workOnElements<
    const PredicateType*,
    SubstitutionType*
    >(element, {
      {"Condition", a_condition},
      {"Then", a_then}
    },
    Parser::uncompliant);

  return sw;
}


const Select_WhenClauses* _Select_WhenClauses(tinyxml2::XMLElement* element) {
  auto swc = new Select_WhenClauses;

  vectorAction<const Select_When*> a_selectwhen = {&swc->when, &_Select_When};
  Parser::workOnElements<
    const Select_When*
    >(element, {
      {"When", a_selectwhen}
    },
    Parser::uncompliant);

  return swc;
}


Sub* _Select(XMLElement* element) {
  auto s = new Select;

  simpleAction<const Select_WhenClauses*> a_whenClauses = {&s->whenClauses, &_Select_WhenClauses};
  simpleAction<SubstitutionType*> a_else = {&s->_else, &_SubstitutionType};
  Parser::workOnElements<
    const Select_WhenClauses*,
    SubstitutionType*
    >(element, {
	{"When_Clauses", a_whenClauses},
	{"Else", a_else},
    },
    Parser::uncompliant);

  return s;
}
