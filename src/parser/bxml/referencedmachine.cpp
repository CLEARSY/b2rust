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
#include "referencedmachine.h"
#include "../parser.h"


using namespace tinyxml2;

const ReferencedMachine* _ReferencedMachine(tinyxml2::XMLElement* element) {
  ReferencedMachine* referencedMachine = new ReferencedMachine;
  simpleAction<const std::string*> a_name = {&referencedMachine->name, &Parser::GetText};
  simpleAction<const std::string*> a_instance = {&referencedMachine->instance, &Parser::GetText};
  simpleAction<const Parameters*> a_parameters = {&referencedMachine->parameters, &_Parameters};

  Parser::workOnElements<const std::string*, const Parameters*>(element, {
      {"Attr", nullopt},
      {"Name", a_name},
      {"Instance", a_instance},
      {"Parameters", a_parameters}
    },
    Parser::uncompliant);

  return referencedMachine;
}
