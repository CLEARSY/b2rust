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
#include "r_if.h"
#include "../parser/bxml/ifsub.h"

RustIf::RustIf(const RustPredicate* const predicate_arg, std::vector<const RustInstruction*>* const then_arg, std::vector<const RustInstruction*>* const else_arg) :
  predicate(predicate_arg),
  then_instr(then_arg),
  else_instr(else_arg) {
}


void IfSub::ConvertMe(const Context* context, std::vector<const RustInstruction*>* instructions) const {
  auto r_then = new std::vector<const RustInstruction*>;  
  then->ConvertMe(context, r_then);

  auto r_else = new std::vector<const RustInstruction*>;
      
  if (_else != NULL) {
    _else->ConvertMe(context, r_else);
  }

  instructions->push_back(new const RustIf(
			  condition->pred_group->ConvertMe(context),
			  r_then,
			  r_else
					   ));
}
