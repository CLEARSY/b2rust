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
// THE TEMPLATE IMPLEMENTATIONS

// Needed imports
const Exp* _IntegerLiteral(tinyxml2::XMLElement*);
const Exp* _BooleanLiteral(tinyxml2::XMLElement*);
const Exp* _StringLiteral(tinyxml2::XMLElement*);
const Exp* _BinaryExp(tinyxml2::XMLElement*);
const Exp* _NaryExp(tinyxml2::XMLElement*);
const Exp* _EmptySet(tinyxml2::XMLElement*);
const Exp* Exp_Id(tinyxml2::XMLElement*);
const Exp* _BooleanExp(tinyxml2::XMLElement*);

template <typename... Ts>
void workOnElementsSimpleExpSpecific(XMLElement* const element,
				     std::map<std::string, elementAction<Ts...>>* actions,
				     const Exp** obj) {
  // Needs to add actions to the `map`.
  simpleAction<const Exp*> a_id = {obj, &Exp_Id};
  simpleAction<const Exp*> a_integerliteral = {obj, &_IntegerLiteral};
  simpleAction<const Exp*> a_booleanliteral = {obj, &_BooleanLiteral};
  simpleAction<const Exp*> a_booleanexp = {obj, &_BooleanExp};
  simpleAction<const Exp*> a_stringliteral = {obj, &_StringLiteral};
  simpleAction<const Exp*> a_binaryexp = {obj, &_BinaryExp};
  simpleAction<const Exp*> a_emptyset = {obj, &_EmptySet};
  simpleAction<const Exp*> a_naryexp = {obj, &_NaryExp};
  actions->insert({
      {"Id", a_id},
      {"Unary_Exp", nullopt},
      {"EmptySeq", nullopt},
      {"Boolean_Exp",a_booleanexp},
      {"Quantified_Exp",nullopt},
      {"Integer_Literal", a_integerliteral},
      {"Boolean_Literal", a_booleanliteral},
      {"STRING_Literal", a_stringliteral},
      {"Binary_Exp", a_binaryexp},
      {"EmptySet", a_emptyset},
      {"Nary_Exp", a_naryexp}
    });

  Parser::workOnElements<Ts...>(element, *actions, Parser::nonTranslatableYet);
}


template <typename... Ts>
void workOnElementsVectorExpSpecific(XMLElement* const element,
				     std::map<std::string, elementAction<Ts...>>* actions,
				     std::vector<const Exp*>* obj) {
  // Needs to add actions to the `map`.
  vectorAction<const Exp*> a_id = {obj, &Exp_Id};
  vectorAction<const Exp*> a_integerliteral = {obj, &_IntegerLiteral};
  vectorAction<const Exp*> a_booleanliteral = {obj, &_BooleanLiteral};
  vectorAction<const Exp*> a_booleanexp = {obj, &_BooleanExp};
  vectorAction<const Exp*> a_stringliteral = {obj, &_StringLiteral};
  vectorAction<const Exp*> a_binaryexp = {obj, &_BinaryExp};
  vectorAction<const Exp*> a_emptyset = {obj, &_EmptySet};
  vectorAction<const Exp*> a_naryexp = {obj, &_NaryExp};
  actions->insert({
      {"Id", a_id},
      {"Unary_Exp", nullopt},
      {"EmptySeq", nullopt},
      {"Boolean_Exp",a_booleanexp},
      {"Quantified_Exp",nullopt},
      {"Integer_Literal", a_integerliteral},
      {"Boolean_Literal", a_booleanliteral},
      {"STRING_Literal", a_stringliteral},
      {"Binary_Exp", a_binaryexp},
      {"EmptySet", a_emptyset},
      {"Nary_Exp", a_naryexp}
    });

  Parser::workOnElements<Ts...>(element, *actions, "Error: you likely used an instruction which is not translatable by b2rust yet.\n");
}
