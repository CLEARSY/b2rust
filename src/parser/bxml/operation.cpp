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
#include "operation.h"
#include "../bxml/machine.h"
#include "./assignementsub.h"
#include "./operationcall.h"
#include "./sub.h"




Operation* _Operation(XMLElement* element) {
  Operation* o = new Operation;

  attributeActions actions = {
    {"name", &o->name},
  };
  Parser::workOnAttributes(element, &actions, Parser::uncompliant);

  // simpleAction<const Attr*> a_attr = {&o->attr, &_Attr};
  simpleAction<const VariablesType*> a_outputparameters = {&o->outputParameters, &_VariablesType};
  simpleAction<const VariablesType*> a_inputparameters = {&o->inputParameters, &_VariablesType};
  simpleAction<const Invariant*> a_precondition = {&o->precondition, &_Invariant};
  simpleAction<Initialisation*> a_body = {&o->body, &_Initialisation};
  
  Parser::workOnElements<
    Initialisation*,
    const Invariant*,
    const VariablesType*
    >(element, {
	// {"Attr", a_attr},
	{"Refines", std::nullopt},
	{"Output_Parameters", a_outputparameters},
	{"Input_Parameters", a_inputparameters},
	// There are no precondition in the invariant. This parsing is relevant for machine only, however, we do not do any optimisation for now.
	{"Precondition", a_precondition},
	{"Body", a_body},
      },
      Parser::uncompliant);
  
  return o;
}
