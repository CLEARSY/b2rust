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
#ifndef H_PREDGROUP
#define H_PREDGROUP

#include "../parser.h"
#include "../../converter/r_predicate/r_predicate.h"
#include "../../converter/types.h"


// It is a `choice` which contains:
// `BinaryPred`, `ExpComparison`, `QuantifiedPred`, `UnaryPred`, `NaryPred`.
// CHOICE
class PredGroup : public Parser {
  template <typename T> friend std::string* printIt(T*);
public:
  // Note: default implem throws an error.
  virtual const RustPredicate* ConvertMe(const Context*) const = 0;
  virtual void DebugMe(std::ostream&) const;

  // Modifies the list by adding the association variable -> type.
  // Default implementation: does nothing. Adds nothing.
  // A reference to a set list absolutely needs to be given.
  virtual void typesListAndCheck(std::unordered_map<std::string, const RustType*>*, std::unordered_map<std::string, const std::string*>*) const;

  friend std::ostream& operator<<(std::ostream& os, const PredGroup*);


private:
  virtual std::string* debugMe() const = 0;
};


// Calls `workOnElements` but automatically adds simple actions for `PredGroup` (which detects several elements name). The `map` should just ignore the `PredGroup` parsing. However, a reference to the object binded to the pred should be given.
// Caution, the template must include `const PredGroup*`.
template <typename... Ts>
void workOnElementsSimplePredGroupSpecific(XMLElement*, std::map<std::string, elementAction<Ts...>>*, const PredGroup**);

// The same, but with vector actions. So, adds vectorActions for `PredGroup`.
template <typename... Ts>
void workOnElementsVectorPredGroupSpecific(XMLElement*, std::map<std::string, elementAction<Ts...>>*, std::vector<const PredGroup*>*);



#include "predgroup.tcc"

#endif
