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
#ifndef H_VARIN
#define H_VARIN

#include "sub.h"

class VarIn : public Sub {
public:
  // --- FIELDS CONTAINING INFORMATION filled by the Checker so that they can be transmitted to the translater. So, just after the parsing, they have to be empty.

  // The types of local variables.
  std::unordered_map<std::string, const RustType*> types;
  
  // --- END OF EXCEPTIONNAL FIELDS
  
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.
  // const Attr* attr = nullptr;

  // Exactly one.
  const VariablesType* variables;

  // Exactly one.
  SubstitutionType* body;


  // --- ATTRIBUTES ---

  // --- TOOLS ---
  void ConvertMe(const Context*, std::vector<const RustInstruction*>*) const;
  void checkMe(machineType, std::unordered_map<std::string, const std::string*>*);
  void DebugMe(std::ostream&) const;
};


Sub* _VarIn(tinyxml2::XMLElement*);

#endif
