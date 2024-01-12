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
#ifndef H_R_MISCELLANEOUS
#define H_R_MISCELLANEOUS

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "types.h"


class Function;

// A `Context` is unique per module, but can be: 1) Modified before `OPERATIONS` clause; 2) Inside `OPERATION`, cloned and modified.
class Context {
  template <typename T> friend std::string* printIt(T*);
public:
  //  --- VARIABLES CONTEXT
  // Useful to know whether we want dereferencing or something else...
 
  // The list of variables defined in the module/struct (they must be preceded by `self.` in the Rust code). 
  std::unordered_map<std::string, const RustType*> globalVariables;

  // The list of constants defined in the module/struct (they must be preceded by `Self::` in the Rust code). 
  std::unordered_map<std::string, const RustType*> globalConstants;

  // List of variables defined in the operation the expression is in. 
  std::unordered_map<std::string, const RustType*> parameters;

  // List of local variables.
  std::unordered_map<std::string, const RustType*> local;

  // List of local function, other module is not allowed to use function defined in this map
  std::unordered_map<std::string, const Function*>* localFunctions = new std::unordered_map<std::string, const Function*>();

  // Concerning the sets, two `maps`:
  // Association between an enumerator and its enum;
  const std::unordered_map<std::string, const std::string*>* enumeratorsSet;


  // Association between a variable and a pair where :
  // pair.first is the path (represented as enums of renamed module from current module
  // pair.second is the path (represented as enums of not renamed module from current module
  std::unordered_map< std::string, std::vector<std::pair<std::string, std::string>>*> variableNameAssoc;


  // Association between a constant and the referencec machine original name
  std::unordered_map< std::string, const std::string*> constantNameAssoc;

  std::unordered_set<const std::string*> referencedMachineNames; 

  // The list of asociations between an instance of an imported machine name and a name formatted by b2rust.
  std::unordered_map<std::string, const std::string*> instancesNameAssoc;

  // Now, the list of associations between an operation (function) name and the renamed name of the imported module we can find it in.
  std::unordered_map<std::string, const std::string*> operationNameAssoc;

 // The list of asociations between an instance of an imported machine name and a the original machine name.
 // Note that if a machine is imported multiple times, this map would be broken, however the instances Name assoc will be not empty , please manipulate both map
  std::unordered_map<std::string, const std::string*> machineNameAssoc;
  /*!
   * \brief The list of associations between the rust translation of a machine and its type
   */
  std::unordered_map<std::string, std::string> machineTypeAssoc;

  const std::string* getFormatedMachineName(std::string) const;

    
private:
  std::string* debugMe() const;
  
};

#endif
