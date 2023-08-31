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
#ifndef H_BINARY_PRED
#define H_BINARY_PRED

#include "predgroup.h"
#include "binarypredop.h"

class BinaryPred : public PredGroup {
public:
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.
  // const Attr* attr = nullptr;

  // Exactly two.
  std::vector<const PredGroup*> predGroup;


  // --- ATTRIBUTES ---
  // Requires.
  const binaryPredOp* op;


  // --- TOOLS ---
  const RustPredicate* ConvertMe(const Context*) const;  
  // There’s nothing interesting her
  std::string* debugMe() const;
};


const PredGroup* _BinaryPred(tinyxml2::XMLElement*);

#endif
