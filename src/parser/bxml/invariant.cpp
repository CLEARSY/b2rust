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
#include "invariant.h"
#include "narypred.h"
#include "unarypred.h"
#include "../bxml/expcomparison.h"


const Invariant* _Invariant(XMLElement* element) {
  Invariant* i = new Invariant;

  workOnElementsSimplePredGroupSpecific<const PredGroup*>(element, new std::map<std::string, elementAction<const PredGroup*>>, &i->predGroup);

  return i;
}


const Invariant* a_Invariant(XMLElement* element) {
  Invariant* i = new Invariant;

  // TODO.
  // We don’t want to parse anything else than `ExpComparison`. I think...
  simpleAction<const PredGroup*> a_narypred = {&i->predGroup, &a_NaryPred};
  simpleAction<const PredGroup*> a_expcomparison = {&i->predGroup, &a_ExpComparison};
  
  Parser::workOnElements<const PredGroup*>(element, {
      // {"Attr", a_attr},
      {"Binary_Pred", std::nullopt},
      {"Exp_Comparison", a_expcomparison},
      {"Nary_Pred", a_narypred},
      {"Quantified_Pred", std::nullopt},
      {"Unary_Pred", std::nullopt}
    },
    "Error: it seems your files are not BXML 1.0 compliant.\n");

  return i;
}
