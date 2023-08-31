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
#include "operationcall.h"


const OperationCall_Name_Id* _OperationCall_Name_Id(tinyxml2::XMLElement* element) {
  OperationCall_Name_Id* operationcallnameid = new OperationCall_Name_Id;

  attributeActions actions = {
    {"value", &operationcallnameid->value},
    {"instance", &operationcallnameid->instance},
    {"component", &operationcallnameid->component},
  };
  Parser::workOnAttributes(element, &actions, Parser::uncompliant);

  // No elements parsing for now.
  return operationcallnameid;
}


const OperationCall_Name* _OperationCall_Name(tinyxml2::XMLElement* element) {
  OperationCall_Name* operationcallname = new OperationCall_Name;

  simpleAction<const OperationCall_Name_Id*> a_id = {&operationcallname->id, &_OperationCall_Name_Id};
  
  Parser::workOnElements<const OperationCall_Name_Id*>(element, {
      {"Id", a_id}
    }, Parser::uncompliant);

  return operationcallname;
}


Instruction* _OperationCall(tinyxml2::XMLElement* element) {
  OperationCall* operationCall = new OperationCall;
  
  simpleAction<const OperationCall_Name*> a_name = {&operationCall->name, &_OperationCall_Name};
  simpleAction<const __ExpVector*> a_inputParameters = {&operationCall->inputParameters, &___ExpVector};
  simpleAction<const __IdVector*> a_outputParameters = {&operationCall->outputParameters, &___IdVector};
  
  Parser::workOnElements<
    const OperationCall_Name*,
    const __ExpVector*,
    const __IdVector*
    >(element, {
	{"Name", a_name},
	{"Input_Parameters", a_inputParameters},
	{"Output_Parameters", a_outputParameters}
      }, Parser::uncompliant);

  return operationCall;
}
