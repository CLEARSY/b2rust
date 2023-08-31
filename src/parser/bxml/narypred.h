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
#ifndef H_NARYPRED
#define H_NARYPRED

#include "predgroup.h"
#include "../miscellaneous.h"


class NaryPred : public PredGroup {
public:
  const Attr* attr = nullptr;
  const std::string* op;

  // There might be none of them.
  std::vector<const PredGroup*> _pred_group;
  
  const RustPredicateAggregate* ConvertMe(const Context*) const;
  void DebugMe(std::ostream&) const;

  
  void typesListAndCheck(std::unordered_map<std::string, const RustType*>*, std::unordered_map<std::string, const std::string*>*) const;


private:
  std::string* debugMe() const;
};

const PredGroup* _NaryPred(XMLElement*);
// Suitable for abstract machines; compatible with every predicate, but only parses what is interesting for operation preconditions.
const PredGroup* a_NaryPred(tinyxml2::XMLElement*);

#endif
