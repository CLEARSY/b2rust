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
#ifndef H_INTEGERLITERAL
#define H_INTEGERLITERAL

#include "exp.h"

#include <tinyxml2.h>


class IntegerLiteral : public Exp {
public:
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.
  // const Attr* attr = nullptr;


  // --- ATTRIBUTES ---
  const mathint_t* value;
  const mathint_t* typref = nullptr;

  IntegerLiteral();
  IntegerLiteral(mathint_t*);
  // --- TOOLS ---
  const RustExpression* ConvertMe(const Context*) const;
  void DebugMe(std::ostream&) const;
};

const Exp* _IntegerLiteral(tinyxml2::XMLElement*);


#endif
