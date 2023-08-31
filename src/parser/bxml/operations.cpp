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
#include "operations.h"

Operations* _Operations(XMLElement* element) {
    Operations* o = new Operations;

  simpleAction<const Attr*> a_attr = {&o->attr, &_Attr};
  vectorAction<Operation*> a_operations = {&o->operations, &_Operation};

  Parser::workOnElements<const Attr*, Operation*>(element, {
      {"Attr", a_attr},
      {"Operation", a_operations},
    },
    Parser::uncompliant);

  return o;
}
