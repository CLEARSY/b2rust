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
#ifndef H_FUNCTION
#define H_FUNCTION

#include "../parser/bxml/machine.h"
#include "block.h"
#include "r_instruction.h"
#include "r_module.h"

class Function {
public:

  // The function name.
  const std::string name;
  // is it a local function ?
  const bool prive;

  // The list of output parameters. NEEDS to keep the order the user gives, so, we cannot use a classical `std::map`.
  std::vector<std::pair<std::string, const RustType*>> inputParameters;
  std::vector<std::pair<std::string, const RustType*>> outputParameters;

  // The list of instructions.
  std::vector<const RustInstruction*> instructions;

  // Initiates a function from a `Operation` object.
  // The associated `RustModule` has to be given so that the abstract machine can be found. (To get the preconditions...)
  // Other functions might use this shape for the same reason. It is ugly but inheritance is not the solution there.

  // Promoted function, the std::string* pointer indicate the name of the machine who has the implementation
  Function(Context*, const std::string*, const Operation*);

  // The third field indicates should the function be declared as private or public
  Function(Context*, const Operation*, const bool);

  // the field int is useless, it exist just for the surcharge to create a constructor function that has no function body
  Function(Context*, const Operation*, const int);

  // The PrintMe.
  std::string PrintMe() const;

  // The PrintMe case for am
  std::string PrintMe(bool) const;

  friend std::ostream& operator<<(std::ostream& os, const Function*);
};

#endif
