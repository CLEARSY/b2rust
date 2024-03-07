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
#include "binaryexp.h"
#include "../parser.h"
#include "./integerliteral.h"
#include "./naryexp.h"

using namespace tinyxml2;

const Exp* _BinaryExp(XMLElement* element) {
  BinaryExp* be = new BinaryExp;

  attributeActions actions = {{"op", &be->op}, {"typref", &be->typref}};
  Parser::workOnAttributes(element, &actions, Parser::uncompliant);

  workOnElementsVectorExpSpecific<const Exp*>(element, new std::map<std::string, elementAction<const Exp*>>, &be->exp);

  return be;
}

;

std::optional<const Exp*> BinaryExp::isInterval() const {
  // <Binary_Exp op='..' typref='2'>
  //   <Integer_Literal value='0' typref='1'/>
  //   <Integer_Literal value='5' typref='1'/>
  // </Binary_Exp>
  if (*op != ".." || exp.size() != 2) {
    return std::nullopt;
  }

  auto e1 = dynamic_cast<const IntegerLiteral*>(exp.at(0));


  if (!(e1)) {
    // At least one is not an `IntegerLiteral`.
    return std::nullopt;
  }

  if (*e1->value != 0) {
    return std::nullopt;
  }


  return exp.at(1);


}

void BinaryExp::collectLeaf(const Exp* expression, std::vector<const Exp*>* result) const {
  auto binaryExpression = dynamic_cast<const BinaryExp*>(expression);
  if (expression->isInterval().has_value()) {
    result->push_back(expression);
  } else if (binaryExpression && *binaryExpression->op == "*s")  {
      for (const auto& subExp : binaryExpression->exp) {
        collectLeaf(subExp, result);
      }
  } else if (dynamic_cast<const NaryExp*>(expression)){
    //do nothing
  } else {
    Report::emitError("Forbidden construction: non interval inside cartesian product");
    Checker::checking_error = true;
  }

}

std::vector<const Exp*>* BinaryExp::getLeafs() const {
  std::vector<const Exp*>* res = new std::vector<const Exp*>();
  collectLeaf(this, res);
  return res;
}

std::vector<const Exp*>* BinaryExp::getTupleLeafs() const {
  std::vector<const Exp*>* res = new std::vector<const Exp*>();
  collectTupleLeaf(this, res);
  return res;
}

void BinaryExp::collectTupleLeaf(const Exp* expression, std::vector<const Exp*>* result) const {
  auto binaryExpression = dynamic_cast<const BinaryExp*>(expression);
  if (!binaryExpression || *binaryExpression->op != "|->") {
    result->push_back(expression);
  } else {
    // binary expression and op = "|->"
    for (const auto& subExp : binaryExpression->exp) {
      collectTupleLeaf(subExp, result);
    }
  }
}
