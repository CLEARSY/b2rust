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
#include "./assignementsub.h"
#include "./operationcall.h"
#include "assertion.h"
#include "../bxml/ifsub.h"
#include "./skip.h"
#include "narysub.h"


Sub* _VarIn(tinyxml2::XMLElement*);
Sub* _IfSub(tinyxml2::XMLElement*);
Sub* _Select(tinyxml2::XMLElement*);
Sub* _While(tinyxml2::XMLElement*);
Sub* _CaseSub(tinyxml2::XMLElement*);


// Machine for template functions.

template <typename... Ts>
void workOnElementsSimpleSubSpecific(XMLElement* element, std::map<std::string, elementAction<Ts...>>* actions, Sub** the_sub) {
  simpleAction<Sub*> a_assertsub = {the_sub, &_Assertion};
  simpleAction<Sub*> a_assignmentsub = {the_sub, &_AssignementSub};
  simpleAction<Sub*> a_becomesin = {the_sub, &_BecomesIn};
  simpleAction<Sub*> a_becomessuchthat = {the_sub, &_BecomesSuchThat};
  simpleAction<Sub*> a_caseSub = {the_sub, &_CaseSub};
  simpleAction<Sub*> a_ifsub = {the_sub, &_IfSub};
  simpleAction<Sub*> a_narysub = {the_sub, &_NarySub};
  simpleAction<Sub*> a_operationcall = {the_sub, &_OperationCall};
  simpleAction<Sub*> a_select = {the_sub, &_Select};
  simpleAction<Sub*> a_skip = {the_sub, &_Skip};
  simpleAction<Sub*> a_varin = {the_sub, &_VarIn};
  simpleAction<Sub*> a_while = {the_sub, &_While};

  actions->insert({
      {"Assert_Sub", a_assertsub},
      {"Assignement_Sub", a_assignmentsub},
      {"Becomes_In", a_becomesin},
      {"Becomes_Such_That",a_becomessuchthat},
      {"Case_Sub", a_caseSub},
      {"ANY_Sub",std::nullopt},
      {"If_Sub", a_ifsub},
      {"Nary_Sub", a_narysub},
      {"Operation_Call", a_operationcall},
      {"Select", a_select},
      {"Skip", a_skip},
      {"VAR_IN", a_varin},
      {"While", a_while},
    });
  
  Parser::workOnElements<Ts...>(element, *actions, Parser::nonTranslatableYet); 
}


template <typename... Ts>
void workOnElementsVectorSubSpecific(XMLElement* element, std::map<std::string, elementAction<Ts...>>* actions, std::vector<Sub*>* subs) {
  vectorAction<Sub*> a_assertsub = {subs, &_Assertion};
  vectorAction<Sub*> a_assignmentsub = {subs, &_AssignementSub};
  vectorAction<Sub*> a_becomesin = {subs, &_BecomesIn};
  vectorAction<Sub*> a_becomessuchthat = {subs, &_BecomesSuchThat};
  vectorAction<Sub*> a_caseSub = {subs, &_CaseSub};
  vectorAction<Sub*> a_ifsub = {subs, &_IfSub};
  vectorAction<Sub*> a_narysub = {subs, &_NarySub};
  vectorAction<Sub*> a_operationcall = {subs, &_OperationCall};
  vectorAction<Sub*> a_select = {subs, &_Select};
  vectorAction<Sub*> a_skip = {subs, &_Skip};
  vectorAction<Sub*> a_varin = {subs, &_VarIn};
  vectorAction<Sub*> a_while = {subs, &_While};

  actions->insert({
      {"Assert_Sub", a_assertsub},
      {"Assignement_Sub", a_assignmentsub},
      {"Becomes_In", a_becomesin},
      {"Becomes_Such_That", a_becomessuchthat},
      {"Case_Sub", a_caseSub},
      {"ANY_Sub",std::nullopt},
      {"If_Sub", a_ifsub},
      {"Nary_Sub", a_narysub},
      {"Operation_Call", a_operationcall},
      {"Select", a_select},
      {"Skip", a_skip},
      {"VAR_IN", a_varin},
      {"While", a_while},
    });
  
  Parser::workOnElements<Ts...>(element, *actions, Parser::nonTranslatableYet); 
}
