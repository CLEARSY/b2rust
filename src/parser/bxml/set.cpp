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
#include "set.h"


const Set* _Set(tinyxml2::XMLElement* element) {
  Set* s = new Set;

  simpleAction<const Id*> a_id = {&s->id, &_Id};
  simpleAction<const EnumeratedValues*> a_enumeratedValues = {&s->enumeratedValues, &_EnumeratedValues};

  Parser::workOnElements<
    const Id*,
    const EnumeratedValues*
    >(element, {
	{"Attr", nullopt},
	{"Id", a_id},
	{"Enumerated_Values", a_enumeratedValues}
      },
      Parser::uncompliant);

  return s;
}
