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
#ifndef H_ID
#define H_ID

#include "exp.h"

#include <tinyxml2.h>


class Id : public Exp {
  template <typename T> friend std::string* printIt(T*);
public:
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.
  // const Attr* attr = nullptr;


  // --- ATTRIBUTES ---
  const std::string* value;
  const std::string* instance = nullptr;
  const std::string* component = nullptr;
  const unsigned* suffix = nullptr;
  const cpp_int* typref = nullptr;

  

  // --- TOOLS
  const RustType* RightExprType(std::unordered_map<std::string, const std::string*>*) const;
  
  const RustExpression* ConvertMe(const Context*) const;
  void DebugMe(std::ostream&) const;
  std::optional<const Exp*> isInterval() const;

private:
  std::string* debugMe() const;

  friend std::ostream& operator<<(std::ostream& os, const Id*); 
};


const Id* _Id(tinyxml2::XMLElement*);
const Exp* Exp_Id(tinyxml2::XMLElement*);


// `__IdVector` isn’t a name you may find in the BXML specification; it could be associated with an element which contains exactly at least ONE `Id`.
class __IdVector : public Parser {
  template <typename T> friend std::string* printIt(T*);
  
public:
  // --- ELEMENTS ---
  // min: 1, max: unbounded.
  std::vector<const Id*> id;


  // --- ATTRIBUTES ---
private:
  std::string* debugMe() const;
};

const __IdVector* ___IdVector(tinyxml2::XMLElement*);

#endif
