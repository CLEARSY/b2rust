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
#ifndef H_R_ASSIGNEMENT
#define H_R_ASSIGNEMENT

#include <string>
#include <variant>

#include "r_expression.h"
#include "r_instruction.h"
#include "./miscellaneous.h"


// To make the difference with the `Instruction` class of the machine.
class RustAssignement : public RustInstruction {
public:
  // Construct an assignement from the left and the right member.
  RustAssignement(const RustExpression*, const RustExpression*);
  
  const Variable* variable;
  const RustExpression* const leftExpression;
  const RustExpression* const rightExpression;

  std::string PrintMe() const;
  std::string PrintMeInit() const;
  std::string PrintMeInit2() const;
  void DebugMe(std::ostream&) const;
};


#endif
