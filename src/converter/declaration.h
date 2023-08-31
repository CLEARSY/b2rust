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
#ifndef H_DECLARATION
#define H_DECLARATION

#include "r_instruction.h"
#include "./types.h"
#include "r_expression.h"

/* Declaration (using the `let` keyword). Used, for example, in locale variable definition. */
class Declaration : public RustInstruction {
public:
  Declaration(const std::string*, const RustType*);
  Declaration(const std::string*, const RustExpression*);
  Declaration(const std::string*,  const RustExpression*,  const RustType*);
  // The name of the new variable.
  const std::string* name;

  // Its type.
  const RustType* type = nullptr;

  //Its Expression
  const RustExpression* expr = nullptr;
 
  std::string PrintMe() const;
  std::string PrintMeInit() const;
  void DebugMe(std::ostream& os) const;
};

#endif
