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
#ifndef H_VALUATION
#define H_VALUATION

#include "../parser.h"
#include "./exp.h"


// A container of `Exp` (like `expression_type`), but with some added details.
class Valuation {
public:
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.
  // const Attr* attr = nullptr;

  // exactly one
  const Exp* exp;


  // --- ATTRIBUTES ---
  const std::string* ident;
  const cpp_int* typref = nullptr;
};

const Valuation* _Valuation(XMLElement*);


#endif
