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
#ifndef H_SUB
#define H_SUB


#include "instruction.h"

using Sub = Instruction;


// Calls `workOnElements` but automatically adds simple actions for `Sub` (which detects several elements name). The `map` should just ignore the `Sub` parsing. However, a reference to the object binded to the sub should be given.
// Caution, the template must include `Sub*`.
template <typename... Ts>
void workOnElementsSimpleSubSpecific(XMLElement*, std::map<std::string, elementAction<Ts...>>*, Sub**);

// The same, but for vector actions.
template <typename... Ts>
void workOnElementsVectorSubSpecific(XMLElement*, std::map<std::string, elementAction<Ts...>>*, std::vector<Sub*>*);


// Template.
#include "sub.tcc"

#endif
