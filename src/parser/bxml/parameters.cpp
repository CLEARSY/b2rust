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
#include "parameters.h"


const Parameters* _Parameters(tinyxml2::XMLElement* element) {
  Parameters* par = new Parameters;

  workOnElementsVectorExpSpecific<const Exp*>(element, new std::map<std::string, elementAction<const Exp*>>, &par->expr);

  return par;
}
