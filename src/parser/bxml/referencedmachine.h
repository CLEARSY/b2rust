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
#ifndef H_REFERENCED_MACHINE
#define H_REFERENCED_MACHINE

#include "../parser.h"
#include "parameters.h"

#include <tinyxml2.h>


class ReferencedMachine {
  template <typename T> friend std::string* printIt(T*);
public:
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.
  /* const Attr* attr = nullptr; */

  /* exactly one */
  const std::string* name;

  // min: 0, max: 1
  const std::string* instance = nullptr;

  // min: 0, max: 1
  const Parameters* parameters = nullptr;
  

  // --- ATTRIBUTES ---
  
  // --- TOOLS ---
  void checkMe(machineType, std::unordered_map<std::string, const std::string*>*) const;
  friend std::ostream& operator<<(std::ostream& os, const ReferencedMachine*);
  
private:
  std::string* debugMe() const;
};

const ReferencedMachine* _ReferencedMachine(tinyxml2::XMLElement*);


#endif
