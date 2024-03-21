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
#ifndef H_TYPE_INFOS_TYPE
#define H_TYPE_INFOS_TYPE

#include "type.h"

// Just a container for a `Type`. With an attribute, however.
class TypeInfosType {
  template <typename T> friend std::string* printIt(T*);
public:
  // --- ELEMENTS ---
  // exactly one
  const Type* type;

  // --- ATTRIBUTES ---
  // required
  const mathint_t* id;
  
  // --- TOOLS ---
private:
  virtual std::string* debugMe() const;
};

const TypeInfosType* _TypeInfosType(tinyxml2::XMLElement*);

#endif
