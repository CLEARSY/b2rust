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
#ifndef H_SELECT
#define H_SELECT

#include "sub.h"


class Select_When {
public:
  // --- ELEMENTS ---
  // exactly one.
  const PredicateType* condition;

  // exactly one.
  SubstitutionType* then;
};

const Select_When* _Select_When(tinyxml2::XMLElement*);


class Select_WhenClauses {
public:
  // --- ELEMENTS ---
  // min: 1, max: unbounded.
  std::vector<const Select_When*> when;
};

const Select_WhenClauses* _Select_WhenClauses(tinyxml2::XMLElement*);
  

class Select : public Sub {
public:
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.
  // const Attr* attr = nullptr;

  // exactly one.
  const Select_WhenClauses* whenClauses;

  // min: 0, max: 1
  SubstitutionType* _else = nullptr;


  // --- TOOLS ---
  void ConvertMe(const Context*, std::vector<const RustInstruction*>*) const;
  void checkMe(machineType, std::unordered_map<std::string, const std::string*>*);
};

Sub* _Select(tinyxml2::XMLElement*);


#endif
