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
#include "narypred.h"
#include "../bxml/expcomparison.h"
#include "unarypred.h"


const PredGroup* _NaryPred(XMLElement* element) {
  NaryPred* narypred = new NaryPred;
  
  attributeActions actions = {{"op", &narypred->op}};
  Parser::workOnAttributes(element, &actions, Parser::uncompliant);
  
  workOnElementsVectorPredGroupSpecific<const PredGroup*>(element, new std::map<std::string, elementAction<const PredGroup*>>, &narypred->_pred_group);

  return narypred;
}


const PredGroup* a_NaryPred(XMLElement* element) {
  NaryPred* narypred = new NaryPred;
  
  attributeActions actions = {{"op", &narypred->op}};
  Parser::workOnAttributes(element, &actions, Parser::uncompliant);

  simpleAction<const Attr*> a_attr = {&narypred->attr, &_Attr};

  // We shouldn’t parse anything else than `ExpComparison`. I think...
  vectorAction<const PredGroup*> a_expcomparison = {&narypred->_pred_group, &a_ExpComparison};
  
  Parser::workOnElements<const Attr*, const PredGroup*>(element, {
      {"Attr", a_attr},

      {"Binary_Pred", nullopt},
      {"Exp_Comparison", a_expcomparison},
      {"Nary_Pred", nullopt},
      {"Quantified_Pred", nullopt},
      {"Unary_Pred", nullopt}
    },
    Parser::uncompliant);


  return narypred;
}
