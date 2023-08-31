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
#ifndef H_DELEGATECALL
#define H_DELEGATECALL

#include "r_instruction.h"
#include "miscellaneous.h"
#include "./r_expression.h"

#include <vector>


class DelegateCall : public RustInstruction {
  template <typename T> friend std::string* printIt(T*);

public:
  DelegateCall(const std::string* moduleName_arg, const std::string* functionName_arg);

  // The name of the module the function is in. If the instance is not renamed, it will be a bit difficult.
  std::string moduleName;

  // The name of the function to call.
  std::string functionName;

  // Input parameters (as Rust borrows). The order has to be kept, of course.
  std::vector<const std::string*> inputParameters;

  // Output parameters (as Rust mutable borrows). The order has to be kept, of course. They are `Id`s. So, they are associated with just `Variable`s in the Rust code (because they can be anything). For convenience, we write them as `RustExpression`s --- but there are just `Variable`s.
  std::vector<const std::string*> outputParameters;


  std::string PrintMe() const;

private:
  std::string* debugMe() const;
};

#endif
