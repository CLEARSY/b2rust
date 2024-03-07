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
#ifndef H_INSTRUCTION
#define H_INSTRUCTION

#include "tinyxml2.h"
using namespace tinyxml2;

#include "../parser.h"
#include "../../converter/r_assignement.h"
#include "../../converter/r_instruction.h"
#include "../miscellaneous.h"
#include "../../converter/miscellaneous.h"
#include "expressiontype.h"
#include "predicatetype.h"

#include <variant>


typedef enum instruction {
  ImAssertion,
  ImNarySub,
  ImSomethingElse
} instructionType;

class NarySub;
class BecomesIn;

class Instruction : public Parser {
public:
  // By default, the conversion fails.
  virtual void ConvertMe(const Context* context, std::vector<const RustInstruction*>*) const = 0;

  // For the checker.
  // Non necessarily const; some works may modify convenience fields.
  virtual void checkMe(machineType, std::unordered_map<std::string, const std::string*>*) = 0;
  instructionType whoami = ImSomethingElse;
  virtual const NarySub* ToNarySub() const;
  virtual const BecomesIn* ToBecomesIn() const;
    
  // For debugging purposes:
  virtual void DebugMe(std::ostream&) const;
  friend std::ostream& operator<<(std::ostream&, Instruction*);
};




// The `BecomesIn` is not an instruction in the B language, but we use it as variable type definition. However, as it can be nested in some instructions like the `VarIn`, we need to consider it as an instruction.
class BecomesIn : public Instruction {
public:
  const Attr* _attr = nullptr;
  const VariablesType* variables;
  const ExpressionType* value;
const BecomesIn* ToBecomesIn() const;
  

  void ConvertMe(const Context* context, std::vector<const RustInstruction*>*) const;
  void DebugMe(std::ostream& os) const;
  void checkMe(machineType, std::unordered_map<std::string, const std::string*>*);
};

Instruction* _BecomesIn(XMLElement*);

class BecomesSuchThat : public Instruction {
public:
  const Attr* _attr = nullptr;
  const VariablesType* variables;
  const PredicateType* pred;

  const BecomesIn* ToBecomesIn() const;
  void ConvertMe(const Context* context, std::vector<const RustInstruction*>*) const;
  void DebugMe(std::ostream& os) const;
  void checkMe(machineType, std::unordered_map<std::string, const std::string*>*);
};

Instruction* _BecomesSuchThat(XMLElement*);
#endif
