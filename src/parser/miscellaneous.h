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
#ifndef H_MISCELLANEOUS
#define H_MISCELLANEOUS

#include <ostream>
#include <tinyxml2.h>
#include <vector>

#include "./bxml/variablestype.h"


class Id;
const Id* _Id(tinyxml2::XMLElement*);

// Useless to parse for now.
class Attr {
public:
  friend std::ostream& operator<<(std::ostream& os, const Attr*); 
};

const Attr* _Attr(tinyxml2::XMLElement*);



// It is exactly the same structure...
using IdentifierListType = VariablesType;
#define _IdentifierListType _VariablesType


#endif
