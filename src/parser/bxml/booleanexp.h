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
#ifndef H_BOOLEANEXP
#define H_BOOLEANEXP

#include <tinyxml2.h>
#include "exp.h"
#include "predgroup.h"

/* Exactly the same as `PredicateType`, but it contains an `Attr`. */
class BooleanExp : public Exp {

public:
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.
  // const Attr* attr = nullptr;

  const PredGroup* predGroup;

private:
  
  void checkMe() const;
  void DebugMe(std::ostream&) const;
  const RustExpression* ConvertMe(const Context*) const;
};

const Exp* _BooleanExp(tinyxml2::XMLElement*);

#endif
