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
#include "r_predicate.h"
#include "../../parser/bxml/predgroup.h"
#include "../../parser/bxml/narypred.h"
#include "../../parser/bxml/unarypred.h"
#include "../../parser/bxml/expcomparison.h"
#include "../../parser/bxml/predicatetype.h"
#include "../../parser/bxml/binarypred.h"
#include "../../util/report.h"

RustBinaryPredicate::RustBinaryPredicate(const comparisonSymbol symbol_arg, const RustExpression* left_expr_arg, const RustExpression* right_expr_arg) :
  symbol(symbol_arg),
  left_expr(left_expr_arg),
  right_expr(right_expr_arg) {
}


const RustPredicate* BinaryPred::ConvertMe(const Context*) const {
  // By default, it is a non-implem thing and it should not be translated.
  Report::emit(Report::Level::FATAL, "Unexpected binary predicate found.");
  return nullptr;
}

const RustBinaryPredicate* ExpComparison::ConvertMe(const Context* context) const {
  // Converting the symbol. For now, this conversion function is here.
  static const std::map<std::string, comparisonSymbol> assoc = {
    {"<i", comparisonSymbol::LessThan},
    {"<=i", comparisonSymbol::LessThanOrEqualTo},
    {"=", comparisonSymbol::EqualTo},
    {"/=", comparisonSymbol::NotEqualTo},
    {">=i", comparisonSymbol::MoreThanOrEqualTo},
    {">i", comparisonSymbol::MoreThan}
  };

  return new RustBinaryPredicate(
				 assoc.at(*op),
				 exp.at(0)->ConvertMe(context),
				 exp.at(1)->ConvertMe(context)
				 );
}


RustPredicateAggregate::RustPredicateAggregate(const comparisonSymbol symbol_arg, const std::vector<const RustPredicate*>* predicates_arg) :
  symbol(symbol_arg),
  predicates(predicates_arg) {
}


const RustPredicateAggregate* NaryPred::ConvertMe(const Context* context) const {
  static const std::map<std::string, comparisonSymbol> assoc = {
    {"&", comparisonSymbol::And},
    {"or", comparisonSymbol::Or}
  };

  auto predicates = new std::vector<const RustPredicate*>;
  for (const PredGroup* predicate : _pred_group) {
    predicates->push_back(predicate->ConvertMe(context));
  }
  // To correct.
  // std::transform(pred_group->begin(), pred_group->end(), predicates->begin(), [] (constPredGroup const pred) {return pred->ConvertMe();});

  return new const RustPredicateAggregate(assoc.at(*op), predicates);
}


RustUnaryPredicate::RustUnaryPredicate(const RustPredicate* predicate_arg) :
  predicate(predicate_arg) {
}


const RustUnaryPredicate* UnaryPred::ConvertMe(const Context* context) const {
  return new RustUnaryPredicate(pred_group->ConvertMe(context));
}
