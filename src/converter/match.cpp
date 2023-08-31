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
#include "match.h"
#include "../parser/bxml/case_sub.h"
#include "block.h"
#include "miscellaneous.h"

Match::Match(const RustExpression* const target_arg, std::vector<const RustCase*>* const r_case_arg, const Block* else_arg)
    : target(target_arg),
      cases(r_case_arg),
      _default(else_arg) {}

void CaseSub::ConvertMe(const Context* context, std::vector<const RustInstruction*>* instructions) const {
  auto ncases = new std::vector<const RustCase*>;

  for (const auto* choice : (choices->choices)) {
    auto ncase_inst = new std::vector<const RustInstruction*>;
    (choice->then)->ConvertMe(context, ncase_inst);
    auto body = new Block(ncase_inst);

    auto nvalues = new std::vector<const RustExpression*>;
    for (size_t i = 0; i < choice->value.size(); i++) {
      nvalues->push_back(choice->value.at(i)->exp->ConvertMe(context));
    }

    ncases->push_back(new RustCase(nvalues, body));
  }

  auto ndefault = new std::vector<const RustInstruction*>;
  if (_else != NULL) {
    _else->ConvertMe(context, ndefault);
  }

  instructions->push_back(new Match((value->exp)->ConvertMe(context), ncases, new Block(ndefault)));
};
