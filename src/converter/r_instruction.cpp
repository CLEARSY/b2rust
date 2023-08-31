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
#include "r_instruction.h"

#include "../converter/declaration.h"
#include "../debug.h"
#include "../parser/bxml/id.h"
#include "../parser/bxml/instruction.h"
#include "../parser/bxml/substitutiontype.h"

void SubstitutionType::ConvertMe(const Context* context, std::vector<const RustInstruction*>* instructions) const {
  // It is just a nested instruction...
  sub->ConvertMe(context, instructions);
}

void BecomesIn::ConvertMe(const Context* context, std::vector<const RustInstruction*>* instructions) const {
  // If the checker worked, we know the `BecomesIn` is a declaration of a new locale variable.
  const std::string* typedVar = (*variables->id.begin())->value;

  const Variable* var = _Variable(context, typedVar);


  if (var->getType()) {
    instructions->push_back(new Declaration(typedVar,                                          
                                            var->getType()->convertIfPartial(context)));
  } else {
    instructions->push_back(new Declaration(typedVar,
                                            var->getType()));
  }

}

void BecomesSuchThat::ConvertMe(const Context* context, std::vector<const RustInstruction*>* instructions) const {
  // If the checker worked, we know the `BecomesSuchThat` is a declaration of a new locale variable.
  const std::string* typedVar = (*variables->id.begin())->value;
  const Variable* var = _Variable(context, typedVar);

  if (var->getType()) {
    instructions->push_back(new Declaration(typedVar,
                                            // The type can be got from the `types` `map`.
                                            var->getType()->convertIfPartial(context)));
  } else {
    instructions->push_back(new Declaration(typedVar,
                                            // The type can be got from the `types` `map`.
                                            var->getType()));
  }

}