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
#include "assignementsub.h"
#include "../parser.h"
#include "../../debug.h"


Instruction* _AssignementSub(XMLElement* element) {
  AssignementSub* as = new AssignementSub;

  simpleAction<const __ExpVector*> a_variables = {&as->variables, &___ExpVector};
  simpleAction<const __ExpVector*> a_values = {&as->values, &___ExpVector};

  Parser::workOnElements<
    const __ExpVector*
    >(element, {
      {"Attr", nullopt},	    
      {"Variables", a_variables},
      {"Values", a_values}
    }, Parser::uncompliant);

  return as;
}
