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
#ifndef H_MATCH
#define H_MATCH

#include "r_expression.h"
#include "r_instruction.h"
#include "block.h"
#include "r_case.h"
#include "../parser/bxml/case_sub.h"

class Match : public RustInstruction {
public:
  Match(const RustExpression*, std::vector<const RustCase*>*, const Block*);

  const RustExpression* target;
  std::vector<const RustCase*>* const cases;
  
  const Block* const _default;

  std::string PrintMe() const;
  void DebugMe(std::ostream&) const;
};





#endif
