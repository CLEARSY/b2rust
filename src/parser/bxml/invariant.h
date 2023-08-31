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
#ifndef H_INVARIANT
#define H_INVARIANT

#include "predgroup.h"


/* Exactly the same as `PredicateType`, but it contains an `Attr`. */
class Invariant {
  template <typename T> friend std::string* printIt(T*);
  
public:
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.
  // const Attr* attr = nullptr;

  // There might not be anything for example for uninteresting preconditions of abstract machines.
  // There is one.
  const PredGroup* predGroup;

private:
  std::string* debugMe() const;
};

const Invariant* _Invariant(tinyxml2::XMLElement*);

// Suitable for abstract machines; compatible with every predicate, but only parses what is interesting for operation preconditions.
const Invariant* a_Invariant(tinyxml2::XMLElement*);


#endif
