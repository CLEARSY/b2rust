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
#include "assertion.h"
#include "machine.h"


Instruction* _Assertion(XMLElement* element) {
  Assertion* assert_sub = new Assertion;
  
  // We want no attribute.
  Parser::workOnAttributes(element, {}, "Error: it seems your input files are not BXML 1.0 compliant.\n");

  simpleAction<const PredicateType*> a_guard = {&assert_sub->guard, &_PredicateType};
  simpleAction<SubstitutionType*> a_body = {&assert_sub->body, &_SubstitutionType};

  Parser::workOnElements<const PredicateType*, SubstitutionType*>(element, {
      {"Guard", a_guard},
      {"Body", a_body}
    },
    "Error: it seems your input files are not BXML 1.0 compliant.\n");

  
  return assert_sub;
}


