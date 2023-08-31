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
#ifndef H_CASE
#define H_CASE

#include "r_expression.h"
#include "r_instruction.h"
#include "block.h"

class RustCase {
public:
    RustCase(const std::vector< const RustExpression*>* , const Block*);

    const std::vector<const RustExpression*>* value;
    const Block* then;

  std::string PrintMe() const;
  void DebugMe(std::ostream&) const;
};

#endif
