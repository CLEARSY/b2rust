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
#ifndef H_R_IF
#define H_R_IF

#include <string>
#include <vector>

#include "r_instruction.h"
#include "r_expression.h"
#include "r_predicate/r_predicate.h"
  
class RustIf : public RustInstruction {
public:
  RustIf(const RustPredicate*, std::vector<const RustInstruction*>*, std::vector<const RustInstruction*>*);

  const RustPredicate* predicate;
  std::vector<const RustInstruction*>* const then_instr;
  std::vector<const RustInstruction*>* const else_instr;

  std::string PrintMe() const;
  void DebugMe(std::ostream&) const;
};

#endif
