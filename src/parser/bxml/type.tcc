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
template <typename... Ts>
void workOnElementsVectorTypeSpecific(tinyxml2::XMLElement* element, std::map<std::string, elementAction<Ts...>>* actions, std::vector<const Type*>* types) {
  vectorAction<const Type*> a_typeBinaryExp = {types, &_Type_BinaryExp};
  vectorAction<const Type*> a_typeId = {types, &_Type_Id};
  vectorAction<const Type*> a_typeUnaryExp = {types, &_Type_UnaryExp};
  vectorAction<const Type*> a_typeStruct = {types, &_Type_Struct};
  vectorAction<const Type*> a_typeGenericType = {types, &_Type_GenericType};

  actions->insert({
      {"Binary_Exp", a_typeBinaryExp},
      {"Id", a_typeId},
      {"Unary_Exp", a_typeUnaryExp},
      {"Struct", a_typeStruct},
      {"GenericType", a_typeGenericType},
    });
  
  Parser::workOnElements<Ts...>(element, *actions, Parser::uncompliant); 
}


template <typename... Ts>
void workOnElementsSimpleTypeSpecific(tinyxml2::XMLElement* element, std::map<std::string, elementAction<Ts...>>* actions, const Type** type) {
  simpleAction<const Type*> a_typeBinaryExp = {type, &_Type_BinaryExp};
  simpleAction<const Type*> a_typeId = {type, &_Type_Id};
  simpleAction<const Type*> a_typeUnaryExp = {type, &_Type_UnaryExp};
  simpleAction<const Type*> a_typeStruct = {type, &_Type_Struct};
  simpleAction<const Type*> a_typeGenericType = {type, &_Type_GenericType};

  actions->insert({
      {"Binary_Exp", a_typeBinaryExp},
      {"Id", a_typeId},
      {"Unary_Exp", a_typeUnaryExp},
      {"Struct", a_typeStruct},
      {"GenericType", a_typeGenericType},
    });
  
  Parser::workOnElements<Ts...>(element, *actions, Parser::uncompliant); 
}
