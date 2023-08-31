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
#ifndef H_OPERATIONCALL
#define H_OPERATIONCALL

#include "../parser.h"
#include "instruction.h"
#include "../bxml/assignementsub.h"


class OperationCall_Name_Id : public Parser {
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

private:
  std::string* debugMe() const;
};

const OperationCall_Name_Id* _OperationCall_Name_Id(tinyxml2::XMLElement*);


class OperationCall_Name : public Parser {
  template <typename T> friend std::string* printIt(T*);
  
public:
  // --- ELEMENTS ---
  // exactly one
  const OperationCall_Name_Id* id;


  // --- ATTRIBUTES ---
private:
  std::string* debugMe() const;
};

const OperationCall_Name* _OperationCall_Name(tinyxml2::XMLElement*);


class OperationCall : public Instruction {
  template <typename T> friend std::string* printIt(T*);
  
public:
  // --- ELEMENTS ---
  // exactly one
  const OperationCall_Name* name;

  // min: 0, unbounded.
  const __ExpVector* inputParameters = nullptr;

  // min: 0, unbounded.
  // /!\ CAUTION: we suppose there’s an error in the BXML spec and that they are always `Id`.
  const __IdVector* outputParameters = nullptr;


  // --- ATTRIBUTES ---


  // ---CONSTRUCTOR---
 // OperationCall(const OperationCall_Name*,const __ExpVector*, const __IdVector*);

  // --- TOOLS ---
  void ConvertMe(const Context*, std::vector<const RustInstruction*>*) const;
  void checkMe(machineType, std::unordered_map<std::string, const std::string*>*);
  void DebugMe(std::ostream&) const;

private:
  std::string* debugMe() const;
};



Instruction* _OperationCall(tinyxml2::XMLElement*);


#endif
