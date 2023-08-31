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
// Template functions definitions

// Needed imports
const PredGroup* _BinaryPred(tinyxml2::XMLElement*);
const PredGroup* _NaryPred(tinyxml2::XMLElement*);
const PredGroup* _ExpComparison(tinyxml2::XMLElement*);
const PredGroup* _UnaryPred(tinyxml2::XMLElement*);


template <typename... Ts>
void workOnElementsSimplePredGroupSpecific(XMLElement* const element,
					   std::map<std::string, elementAction<Ts...>>* actions,
					   const PredGroup** predicate) {
  // Needs to add actions to the `map`.
  simpleAction<const PredGroup*> a_binarypred = {predicate, &_BinaryPred};
  simpleAction<const PredGroup*> a_narypred = {predicate, &_NaryPred};
  simpleAction<const PredGroup*> a_expcomparison = {predicate, &_ExpComparison};
  simpleAction<const PredGroup*> a_unarypred = {predicate, &_UnaryPred};

  actions->insert({
      {"Binary_Pred", a_binarypred},
      {"Quantified_Pred",nullopt},
      {"Nary_Pred", a_narypred},
      {"Exp_Comparison", a_expcomparison},
      {"Unary_Pred", a_unarypred}
    });

  Parser::workOnElements<Ts...>(element, *actions, "Error: you likely used an instruction which is not translatable by b2rust yet.\n");
}


template <typename... Ts>
void workOnElementsVectorPredGroupSpecific(XMLElement* const element,
					   std::map<std::string, elementAction<Ts...>>* actions,
					   std::vector<const PredGroup*>* predicate) {
  // Needs to add actions to the `map`.
  vectorAction<const PredGroup*> a_binarypred = {predicate, &_BinaryPred};
  vectorAction<const PredGroup*> a_narypred = {predicate, &_NaryPred};
  vectorAction<const PredGroup*> a_expcomparison = {predicate, &_ExpComparison};
  vectorAction<const PredGroup*> a_unarypred = {predicate, &_UnaryPred};

  actions->insert({
      {"Binary_Pred", a_binarypred},
      {"Quantified_Pred",nullopt},
      {"Nary_Pred", a_narypred},
      {"Exp_Comparison", a_expcomparison},
      {"Unary_Pred", a_unarypred},
      
    });

  Parser::workOnElements<Ts...>(element, *actions, Parser::uncompliant);
}
