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
#include "predicatetype.h"
#include "../bxml/ifsub.h"


const PredicateType* _PredicateType(XMLElement* element) {
  PredicateType* predicatetype = new PredicateType;

  // We want no attribute.
  Parser::workOnAttributes(element, {}, "Error: it seems your input files are not BXML 1.0 compliant.\n");

  // We want exactly one subelement which is a pred_group. It is the parsing defined in `If`...
  workOnElementsSimplePredGroupSpecific<const PredGroup*>(element, new std::map<std::string, elementAction<const PredGroup*>>, &predicatetype->pred_group);

  return predicatetype;
}

