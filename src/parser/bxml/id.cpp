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
#include "id.h"
#include "../parser.h"
#include "integerliteral.h"


using namespace tinyxml2;

const Id* _Id(XMLElement* element) {
  Id* id = new Id;

  attributeActions actions = {
  {"value", &id->value}, 
  {"instance", &id->instance},
  {"component", &id->component},
  {"suffix", &id->suffix}, 
  {"typref", &id->typref}
  };
  Parser::workOnAttributes(element, &actions, Parser::uncompliant);

  // Useless for now
  // simpleAction<const Attr*> a_attr = {&id->_attr, &_Attr};

  // Parser::workOnElements<const Attr*>(element, {
  //     {"Attr", a_attr}
  //   },
  //   "Error: it seems your input files are not BXML 1.0 compliant.\n");

  return id;
}

const Exp* Exp_Id(XMLElement* element) { return _Id(element); }

const __IdVector* ___IdVector(XMLElement* element) {
  __IdVector* ev = new __IdVector;

  vectorAction<const Id*> a_id = {&ev->id, &_Id};

  Parser::workOnElements<const Id*>(element, {{"Id", a_id}}, Parser::uncompliant);

  return ev;
}

std::optional<const Exp*> Id::isInterval() const {
     auto it = RustType::types.find(*value);
     
    if (it != RustType::types.end()) {
      cpp_int* val = new cpp_int();
      *val = 0;
      auto detectedType = RustType::types.at(*value);
    // It is a recognized type!
      if (dynamic_cast<const  i16_t*>(detectedType) || dynamic_cast<const i8_t*>(detectedType) || dynamic_cast<const  i32_t*>(detectedType)){
        *val = -1;
      } 

      if (dynamic_cast<const  u8_t*>(detectedType)){
        *val = 255;
      } else if (dynamic_cast<const  u16_t*>(detectedType)){
        *val = 65535;
      } else if (dynamic_cast<const u32_t*>(detectedType)){
        *val = 4294967295;
      } else if (dynamic_cast<const u64_t*>(detectedType)){
        std::string maxU64 = "18446744073709551615";
        *val = boost::multiprecision::cpp_int(maxU64);
        
      } else if (dynamic_cast<const u128_t*>(detectedType)){
        std::string maxU128 = "340282366920938463463374607431768211455";
        *val = boost::multiprecision::cpp_int(maxU128);
      }

      if (*val != 0)
       return new IntegerLiteral(val);

    } 
    return nullopt;
    
};