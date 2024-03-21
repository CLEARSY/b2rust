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
#include "integerliteral.h"
#include "../parser.h"


using namespace tinyxml2;

const Exp* _IntegerLiteral(XMLElement* element) {
  auto il = new IntegerLiteral;

  attributeActions actions = {
    {"value", &il->value},
    {"typref", &il->typref},
  };
  Parser::workOnAttributes(element, &actions, Parser::uncompliant);


  // Useless for now.
  // simpleAction<const Attr*> a_attr = {&il->attr, &_Attr};
  // Parser::workOnElements<const Attr*>(element, {
  //     {"Attr", a_attr}
  //   },
  //   "Error: it seems your files are not BXML 1.0 compliant.\n");

  return il;
}

IntegerLiteral::IntegerLiteral(mathint_t* _value) :
value(_value){}

IntegerLiteral::IntegerLiteral(){
}