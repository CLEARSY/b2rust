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
#ifndef H_DEBUG
#define H_DEBUG

#include <optional>

#include <map>
#include <set>
#include <string>

#include <unordered_map>
#include <unordered_set>

#include <iostream>

#include "parser/bxml/machine.h"
#include "./parser/bxml/machine.h"
#include "./parser/bxml/abstraction.h"
#include "./parser/bxml/binaryexp.h"
#include "converter/r_module.h"
#include "converter/r_if.h"
#include "converter/r_assignement.h"
#include "converter/block.h"
#include "input.h"
#include "printer/printer.h"
#include "./converter/declaration.h"
#include "./parser/expression_leaf.h"
#include "./converter/function.h"
#include "./converter/match.h"

// ostream& operator<<(ostream&, XMLElement*);

std::ostream& operator<<(std::ostream&, exp_type);
std::ostream& operator<<(std::ostream&, const Exp*);
std::ostream& operator<<(std::ostream&, std::map<std::string, const Exp*>::iterator);
std::ostream& operator<<(std::ostream&, std::map<std::string, RecognizedType>);
std::ostream& operator<<(std::ostream&, std::map<const std::string, const RustType*>*);
std::ostream& operator<<(std::ostream&, const comparisonSymbol);
std::ostream& operator<<(std::ostream&, const std::vector<const RustInstruction*>*);
std::ostream& operator<<(std::ostream&, const std::vector<Instruction*>*);
std::ostream& operator<<(std::ostream&, const RecognizedType);
std::ostream& operator<<(std::ostream&, std::set<std::string>);
std::ostream& operator<<(std::ostream& os, binaryExpression);
std::ostream& operator<<(std::ostream&, const std::set<std::string>*);
std::ostream& operator<<(std::ostream&, std::vector<const Id*>*);
std::ostream& operator<<(std::ostream&, const Id*);
std::ostream& operator<<(std::ostream& os, const int* i);
std::ostream& operator<<(std::ostream& os, const unsigned* i);
std::ostream& operator<<(std::ostream&, const Exp*);
std::ostream& operator<<(std::ostream&, const VariablesType*);
std::ostream& operator<<(std::ostream&, const Operations*);
std::ostream& operator<<(std::ostream&, const Invariant*);
std::ostream& operator<<(std::ostream&, const RustType*);
std::ostream& operator<<(std::ostream&, const bool*);
std::ostream& operator<<(std::ostream&, std::optional<std::string>);
std::ostream& operator<<(std::ostream&, const Module* const);
std::ostream& operator<<(std::ostream&, std::unordered_map<std::string, Module>*);
std::ostream& operator<<(std::ostream&, const ReferencedMachine*);

// --------------------------------- TOOLS

// Indent the text by two spaces. The string must end by "\n" and will end by "\n". (So, doesn’t indent the first line.) If the string doesn’t end by "\n", infinite loop :)
std::string* indentMe(const std::string*);

// If `nullptr`, returns `(undefined)`. Else, returns the indented `debugMe()`. Ends by a new line. The first line is NOT indented.
template <typename T> std::string* printIt(T* object) {
  if (!object) return new std::string("(Undefined.)\n");
  return indentMe(object->debugMe());
}

// Overrides for specific types.
// Exception for `std::string`s.
std::string* printIt(const std::string*);
std::string* printIt(const std::string &);
std::string* printIt(const int*);
std::string* printIt(const unsigned int*);
// std::string* printIt(std::map<std::string, const RustType*>*);

// Suppose the vector is always defined. (No `nullptr`.)
template <typename T> std::string* printIt(std::vector<T>* vec) {
  std::string* output = new std::string;
  if (vec->empty()) {
    *output = "it is empty.\n";
    return indentMe(output);
  }
  *output = "it contains:\n";
  for (auto obj : *vec) {
    *output += "  – "+*printIt(obj);
  }
  return indentMe(output);
}


template <typename T> std::string* printIt(const std::vector<T>* vec) {
  std::string* output = new std::string;
  if (vec->empty()) {
    *output = "it is empty.\n";
    return indentMe(output);
  }
  *output = "it contains:\n";
  for (auto obj : *vec) {
    *output += "  – "+*printIt(obj);
  }
  return indentMe(output);
}


template <typename T> std::string* printIt(const std::unordered_set<T>* set) {
  std::string* output = new std::string;
  if (set->empty()) {
    *output = "it is empty.\n";
    return indentMe(output);
  }
  *output = "it contains:\n";
  for (auto obj : *set) {
    *output += "  – "+*printIt(obj);
  }
  return indentMe(output);
}

// Suppose the set is always defined. (No `nullptr`.)
template <typename T> std::string* printIt(std::unordered_set<T>* set) {
  return printIt(new const std::unordered_set<T>(*set));
}


// Suppose the map is always defined. (No `nullptr`.) In any case, the keys are supposed not to be pointers.
template <typename T, typename U> std::string* printIt(const std::unordered_map<T, U>* map) {
  std::string* output = new std::string;
  if (map->empty()) {
    *output = "it is empty.\n";
    return indentMe(output);
  }
  *output = "it contains:\n";
  for (const auto& [first, last] : *map) {
    *output += "  – An association between:\n    1. "+*printIt(&first);
    *output += "    2. "+*printIt(last);
  }
  return indentMe(output);
}

// Suppose the map is always defined. (No `nullptr`.) In any case, the keys are supposed not to be pointers.
template <typename T, typename U> std::string* printIt(std::unordered_map<T, U>* map) {
  std::string* output = new std::string;
  if (map->empty()) {
    *output = "it is empty.\n";
    return indentMe(output);
  }
  *output = "it contains:\n";
  for (const auto& [first, last] : *map) {
    *output += "  – An association between:\n    1. "+*printIt(&first);
    *output += "    2. "+*printIt(last);
  }
  return indentMe(output);
}


// Suppose the map is always defined. (No `nullptr`.) In any case, the keys are supposed not to be pointers.
template <typename T, typename U> std::string* printIt(std::map<T, U>* map) {
  std::string* output = new std::string;
  if (map->empty()) {
    *output = "it is empty.\n";
    return indentMe(output);
  }
  *output = "it contains:\n";
  for (const auto& [first, last] : *map) {
    *output += "  – An association between:\n    1. "+*printIt(&first);
    *output += "    2. "+*printIt(last);
  }
  return indentMe(output);
}



// Function `print` calls `printIt`.
template <typename T> void print(T obj) {
  std::cout << *printIt(obj) << std::endl;
}

#endif
