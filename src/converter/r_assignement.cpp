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
#include "r_assignement.h"

#include "../parser/bxml/id.h"
#include "../parser/bxml/assignementsub.h"


RustAssignement::RustAssignement(const RustExpression* const left_expression, const RustExpression* const right_expression) :
  leftExpression(left_expression),
  rightExpression(right_expression) {
}


void AssignementSub::ConvertMe(const Context* context, std::vector<const RustInstruction*>* instructions) const {
  instructions->push_back(new const RustAssignement(
						    (*variables->exp.begin())->ConvertMe(context),
						    (*values->exp.begin())->ConvertMe(context)));
}
