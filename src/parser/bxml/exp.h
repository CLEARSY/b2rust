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
#ifndef H_EXP
#define H_EXP

#include "../../converter/r_expression.h"
#include "../../converter/types.h"
#include "../parser.h"

#include <set>
#include <tinyxml2.h>
#include <vector>

// It is a `choice` which contains:
// `UnaryPred`, `BinaryExp`, `TernaryExp`, `NaryExp`, `BooleanLiteral`, `BooleanExp`, `EmptySet`, `EmptySeq`, `Id`, `IntegerLiteral`, `QuantifiedExp`,
// `QuantifiedSet`, `StringLiteral`, `Struct`, `Record`, `RealLiteral`, `RecordFieldAccess`.
class Exp {
public:
  virtual const RustExpression* ConvertMe(const Context*) const = 0;

  // For debugging purposes:
  virtual void DebugMe(std::ostream&) const = 0;

  // Might need to be checked (for example with the `NaryPred`).
  virtual void checkMe() const;
  // If the right `Exp` is an `Id` which is a b2rust recognized type, it is returned.
  // Useful for invariant checking.
  virtual const RustType* RightExprType(std::unordered_map<std::string, const std::string*>*) const;

  // Checks if this exp is an interval (so, a `BinaryExp`) which begins by 0 and finishes by an expression
  virtual std::optional<const Exp*> isInterval() const;

};

// As an `Exp` element can have different names (`Id`, ...) and have several other elements arround it, it is impossible to write a function whose
// purpose it to parse exactly one `Exp`. However, you can use `Parser::workOnElementsSimpleExpSpecific` instead. However, concerning an element which
// only contains `Exp`, it is possible and a function which can return a vector of `Exp` will be written.

// `__ExpVector` isn’t a name you may find in the BXML specification; it could be associated with an element which contains exactly at least ONE
// `Exp`.
class __ExpVector : public Parser {
  template <typename T> friend std::string* printIt(T*);

public:
  // --- ELEMENTS ---
  // min: 1, max: unbounded.
  std::vector<const Exp*> exp;

  // --- ATTRIBUTES ---
private:
  std::string* debugMe() const;
};

const __ExpVector* ___ExpVector(tinyxml2::XMLElement*);

// Calls `workOnElements` but automatically adds simple actions for `Exp` (which detects several elements name). The `map` should just ignore the
// `Exp` parsing. However, a reference to the object binded to the exp should be given. Caution, the template must include `const Exp*`.
template <typename... Ts> void workOnElementsSimpleExpSpecific(XMLElement*, std::map<std::string, elementAction<Ts...>>*, const Exp**);

// The same, but with vector actions. So, adds vectorActions for `Exp`.
template <typename... Ts> void workOnElementsVectorExpSpecific(XMLElement*, std::map<std::string, elementAction<Ts...>>*, std::vector<const Exp*>*);

#include "exp.tcc"

#endif
