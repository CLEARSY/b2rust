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
#ifndef H_MACHINE
#define H_MACHINE

#include <tinyxml2.h>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <set>

#include "./operation.h"
#include "operations.h"
#include "../recognized_types.h"
#include "./binaryexp.h"
#include "./valuation.h"
#include "./instancelisttype.h"
#include "./initialisation.h"
#include "./sets.h"
#include "./typeinfos.h"
#include "./promotes.h"
#include "parametersdeclaration.h"
class Machine_Values : public Parser {
public:
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.
  // const Attr* attr = nullptr;

  // min: 1, unbounded.
  std::vector<const Valuation*> valuation;
};

const Machine_Values* _Machine_Values(XMLElement*);

  
class Machine : public Parser {
  template <typename T> friend std::string* printIt(T*);
    
public:
  // Takes the path of the file as argument.
  Machine(tinyxml2::XMLElement*);
 


  //required
  const std::string* name;


  const std::string* useless;

  // min: 0, max: 1
  const std::string* abstraction = nullptr;

  // min: 0, max: 1
  const ParametersDeclaration* parameters = nullptr;

  // min: 0, max: 1
  const InstanceListType* includes = nullptr;

  // min: 0, max: 1.
  const InstanceListType* imports = nullptr;

  // min: 0, max: 1.
  const InstanceListType* sees = nullptr;
  
  // min: 0, max: 1.
  const InstanceListType* extends = nullptr;

  // min: 0, max: 1.
  const Promotes* promotes = nullptr;

  // min: 0, max: 1.
  const Machine_Values* values = nullptr;

  // min: 0, max: 1.
  const Sets* sets = nullptr;

  // min: 0, max: 1.
  const IdentifierListType* abstractConstants = nullptr;
  
  // min: 0, max: 1.
  const VariablesType* concreteConstants = nullptr;

  // min: 0, max: 1.
  const IdentifierListType* abstractVariables = nullptr;

  // min: 0, max: 1.
  const VariablesType* concreteVariables = nullptr;

  // min: 0, max: 1.
  const Invariant* properties = nullptr;

  // min: 0, max: 1.
  const Invariant* invariant = nullptr;

  // min: 0, max: 1
  Initialisation* initialisation = nullptr;

  // min: 0, max: 1
  // Might be modified.
  Operations* operations = nullptr;

  //min: 0, max: 1 
  Operations* localOperations = nullptr;
  
  // min: 0, max: 1
  const TypeInfos* typeInfos = nullptr;

private:
  std::string* debugMe() const;

  friend ostream& operator<<(ostream& os, const Machine* const);
};


#endif
