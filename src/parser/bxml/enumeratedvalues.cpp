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
#include "enumeratedvalues.h"


const EnumeratedValues* _EnumeratedValues(tinyxml2::XMLElement* element) {
  EnumeratedValues* ev = new EnumeratedValues;

  vectorAction<const Id*> a_id = {&ev->id, &_Id};

  Parser::workOnElements<
    const Id*
    >(element, {
	{"Id", a_id}
      },
      Parser::uncompliant);

  return ev;
}
