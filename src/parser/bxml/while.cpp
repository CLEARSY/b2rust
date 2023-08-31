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
#include "while.h"


Sub* _While(tinyxml2::XMLElement* element) {
  While* w = new While;

  simpleAction<const PredicateType*> a_condition = {&w->condition, &_PredicateType};
  simpleAction<SubstitutionType*> a_body = {&w->body, &_SubstitutionType};
  simpleAction<const PredicateType*> a_invariant = {&w->invariant, &_PredicateType};
  simpleAction<const ExpressionType*> a_variant = {&w->variant, &_ExpressionType};

  Parser::workOnElements<
    const PredicateType*,
    SubstitutionType*,
    const ExpressionType*
    >(element, {
	{"Condition", a_condition},
	{"Body", a_body},
	{"Invariant", a_invariant},
	{"Variant", a_variant},
      },
      Parser::uncompliant);

  return w;
}
