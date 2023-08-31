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
#ifndef H_CASE_SUB
#define H_CASE_SUB

#include "instruction.h"
#include "./substitutiontype.h"
#include "../../converter/match.h"

class Choice {
public : 
  /*Choice Elements */
  std::vector<const ExpressionType*> value; 
  SubstitutionType* then;

  void checkMe(machineType, std::unordered_map<std::string, const std::string*>*);
};

Choice* _Choice(XMLElement*);


class Choices {
    public :
  // --- ELEMENTS ---
  // min: 1, unbounded.
  std::vector<Choice*> choices;
  void checkMe(machineType, std::unordered_map<std::string, const std::string*>*);
};

Choices* _Choices(XMLElement*);


class CaseSub : public Instruction {
public : 
  const ExpressionType* value;
  Choices* choices;
  SubstitutionType* _else = nullptr;

  void ConvertMe(const Context*, std::vector<const RustInstruction*>*) const;
  void checkMe(machineType, std::unordered_map<std::string, const std::string*>*);
};

Instruction* _CaseSub(XMLElement*);

#endif
