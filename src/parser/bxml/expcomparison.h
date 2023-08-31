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
#ifndef H_EXPCOMPARISON
#define H_EXPCOMPARISON

#include "../bxml/exp.h"
#include "../bxml/predgroup.h"


class ExpComparison : public PredGroup {
public:
  // const Attr* attr = nullptr;

  std::vector<const Exp*> exp;
  const std::string* op;

  const RustBinaryPredicate* ConvertMe(const Context*) const;
  void DebugMe(std::ostream&) const;
  
  void typesListAndCheck(std::unordered_map<std::string, const RustType*>*, std::unordered_map<std::string, const std::string*>*) const;

private:
  std::string* debugMe() const;
};

const PredGroup* _ExpComparison(XMLElement*);
const PredGroup* a_ExpComparison(XMLElement*);
  

#endif
