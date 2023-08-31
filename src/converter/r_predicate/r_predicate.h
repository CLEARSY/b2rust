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
#ifndef H_R_PREDICATE
#define H_R_PREDICATE

#include <vector>

#include "../r_expression.h"


typedef enum comparisonSymbol {
  LessThan,
  LessThanOrEqualTo,
  EqualTo,
  MoreThanOrEqualTo,
  MoreThan,
  NotEqualTo,

  // Aggregates
  And,
  Or,
} comparisonSymbol;


class RustPredicate : public RustExpression {
public:
  friend std::ostream& operator<<(std::ostream& os, const RustPredicate*);
  const RustType* getType() const;
};

  
class RustBinaryPredicate : public RustPredicate {
public:
  RustBinaryPredicate(const comparisonSymbol, const RustExpression*, const RustExpression*);
    
  const comparisonSymbol symbol;
  const RustExpression* const left_expr;
  const RustExpression* const right_expr;
  
  std::string PrintMe() const;
  void DebugMe(std::ostream&) const;
};


class RustPredicateAggregate : public RustPredicate {
public:
  RustPredicateAggregate(const comparisonSymbol, const std::vector<const RustPredicate*>*);

  const comparisonSymbol symbol;
  const std::vector<const RustPredicate*>* predicates;

  std::string PrintMe() const;
  void DebugMe(std::ostream&) const;
};


class RustUnaryPredicate : public RustPredicate {
public:
  RustUnaryPredicate(const RustPredicate*);

  const RustPredicate* predicate;

  std::string PrintMe() const;
  void DebugMe(std::ostream&) const;
};

#endif
