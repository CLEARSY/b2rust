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
#ifndef H_BINARYEXP
#define H_BINARYEXP

#include "exp.h"

#include <vector>
#include <tinyxml2.h>


class BinaryExp : public Exp {
public:
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.
  // const Attr* attr = nullptr;

  // exactly 2 for `BinaryExp`.
  // At least 1 for `NaryExp`.
  std::vector<const Exp*> exp;


  // --- ATTRIBUTES ---
  const std::string* op;
  const cpp_int* typref = nullptr;


  // --- TOOLS ---
  const RustType* RightExprType(std::unordered_map<std::string, const std::string*>*) const;
  void checkMe() const;
  void checkBothAreInterval() const;
  const RustExpression* ConvertMe(const Context*) const;
  void DebugMe(std::ostream&) const;
  std::optional<const Exp*> isInterval() const;

  std::vector<const Exp*>* getLeafs() const ;
  void collectLeaf(const Exp*, std::vector<const Exp*>*) const;
  
  std::vector<const Exp*>* getTupleLeafs() const ;
  void collectTupleLeaf(const Exp*, std::vector<const Exp*>*) const;
};


const Exp* _BinaryExp(tinyxml2::XMLElement*);


#endif
