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
#include "varin.h"

using namespace tinyxml2;


Sub* _VarIn(XMLElement* element) {
  VarIn* vi = new VarIn;
  
  simpleAction<const VariablesType*> a_variables = {&vi->variables, &_VariablesType};
  simpleAction<SubstitutionType*> a_body = {&vi->body, &_SubstitutionType};

  Parser::workOnElements<
    const VariablesType*,
    SubstitutionType*
    >(element, {
      {"Variables", a_variables},
      {"Body", a_body}
    },
      Parser::uncompliant);

  return vi;
}


