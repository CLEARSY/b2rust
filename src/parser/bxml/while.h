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
#ifndef H_WHILE
#define H_WHILE

#include "sub.h"


class While : public Sub {
  template <typename T> friend std::string* printIt(T*);
public:
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.
  // const Attr* attr = nullptr;

  // Exactly one.
  const PredicateType* condition;

  // Exactly one.
  SubstitutionType* body;

  // Exactly one.
  const PredicateType* invariant;

  // Exactly one.
  const ExpressionType* variant;


  // --- ATTRIBUTES ---


  // --- TOOLS ---
  void ConvertMe(const Context*, std::vector<const RustInstruction*>*) const;
  // There’s nothing to check in particular for `While`. Everything is accepted.
  void checkMe(machineType, std::unordered_map<std::string, const std::string*>*) {};
private:
  std::string* debugMe() const;
};

Sub* _While(tinyxml2::XMLElement*);

#endif
