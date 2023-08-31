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
#include "type.h"


const Type* _Type_BinaryExp(tinyxml2::XMLElement* element) {
  Type_BinaryExp* tbe = new Type_BinaryExp;

  workOnElementsVectorTypeSpecific<const Type*>(element, new std::map<std::string, elementAction<const Type*>>, &tbe->type);

  return tbe;
}


const Type* _Type_Id(tinyxml2::XMLElement* element) {
  Type_Id* ti = new Type_Id;

  attributeActions actions = {
    {"value", &ti->value}
  };
  Parser::workOnAttributes(element, &actions, Parser::uncompliant);

  return ti;
}


const Type* _Type_UnaryExp(tinyxml2::XMLElement* element) {
  Type_UnaryExp* tue = new Type_UnaryExp;

  attributeActions actions = {
    {"op", &tue->op}
  };
  Parser::workOnAttributes(element, &actions, Parser::uncompliant);

  workOnElementsSimpleTypeSpecific<const Type*>(element, new std::map<std::string, elementAction<const Type*>>, &tue->type);

  return tue;
}


const Type* _Type_Struct(tinyxml2::XMLElement* element) {
  Type_Struct* ts = new Type_Struct;

  simpleAction<const Type_Struct_RecordItem*> a_typeStructRecordItem = {&ts->recordItem, &_Type_Struct_RecordItem};
    Parser::workOnElements<const Type_Struct_RecordItem*>(element, {
      {"Record_Item", a_typeStructRecordItem}
    },
    Parser::uncompliant);

  return ts;
}


const Type_Struct_RecordItem* _Type_Struct_RecordItem(tinyxml2::XMLElement* element) {
  Type_Struct_RecordItem* tsri = new Type_Struct_RecordItem;

  attributeActions actions = {
    {"label", &tsri->label}
  };
  Parser::workOnAttributes(element, &actions, Parser::uncompliant);

  workOnElementsSimpleTypeSpecific<const Type*>(element, new std::map<std::string, elementAction<const Type*>>, &tsri->type);

  return tsri;
}


const Type* _Type_GenericType(tinyxml2::XMLElement*) {
  return new Type_GenericType;
}
