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
#ifndef H_OPERATION
#define H_OPERATION

#include <tinyxml2.h>

#include "../../error_codes.h"


#include "instruction.h"
#include "./invariant.h"
#include "./expressiontype.h"
#include "../parser.h"

#include "assertion.h"
#include "narysub.h"
#include "initialisation.h"


class Function;

// typedef std::variant<
//   std::set<std::string>*,
//   Instruction**
//   // Operation*
//   > operationComponents;


class Operation : public Parser {
public:
  // --- FIELDS CONTAINING INFORMATION filled by the Checker so that they can be transmitted to the translater. So, just after the parsing, they have to be empty.

  // The types of input/output parameters.
  // NOTE: it has to be present in the abstract machine as well as in the implementation!!
  // However, it may be `null`.
  std::unordered_map<std::string, const RustType*>* types = nullptr;
    
  // END OF FIELDS CONTAINING INFORMATION, etc. (cf supra)

  
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.
  // const Attr* attr = nullptr;

  // min: 0, max: 1
  // Useless for now.
  // const Attr* refines = nullptr;

  // min: 0, max: 1
  // Note: the BXML version 1.0 says it should be a vector of Exp... We suppose it is an error and is a vector of Id, so, like `VariablesType`.
  const VariablesType* outputParameters = nullptr;

  // min: 0, max: 1
  const VariablesType* inputParameters = nullptr;

  // min: 0, max: 1
  const Invariant* precondition = nullptr;

  // exactly one.
  Initialisation* body;


  // --- ATTRIBUTES ---
  // required
  const std::string* name;


  // --- TOOLS ---
  const Function* ConvertMe(const Context*) const;
  const Function* ConvertMePromoted(const Context*,const std::string * ) const;
  const Function* ConvertMePrivate(const Context* ) const;
  const Function* ConvertMeNoBody(const Context* ) const;
};

Operation* _Operation(tinyxml2::XMLElement*);

  
#endif
