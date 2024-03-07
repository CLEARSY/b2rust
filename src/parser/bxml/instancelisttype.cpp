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
#include "instancelisttype.h"

using namespace tinyxml2;

const InstanceListType* _InstanceListType(XMLElement* element) {
  InstanceListType* instanceListType = new InstanceListType;
  vectorAction<const ReferencedMachine*> a_referencedMachine = {&instanceListType->referencedMachine, &_ReferencedMachine};

  Parser::workOnElements<const ReferencedMachine*>(element, {{"Attr", std::nullopt}, {"Referenced_Machine", a_referencedMachine}}, Parser::uncompliant);

  ;

  // remove b2rusttypes from seen machine ...
  std::vector<const ReferencedMachine*>& i_ref = const_cast<std::vector<const ReferencedMachine*>&>(instanceListType->referencedMachine);
  i_ref.erase(std::remove_if(i_ref.begin(), i_ref.end(),
                             [](const ReferencedMachine* ptr) { return Input::exceptions.find(*ptr->name) != Input::exceptions.end(); }),
              i_ref.end());
  return instanceListType;
}
