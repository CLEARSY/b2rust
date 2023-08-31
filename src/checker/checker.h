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
#ifndef H_CHECKER
#define H_CHECKER

#include <string>
#include <unordered_map>
#include <unordered_set>

class PredGroup;
class RustType;
class Operation;

typedef enum machineType { machine, implementation } machineType;

class Checker {
public:
  static bool checking_error;
};

// Given a `PredGroup` and a list of names, checks that the `PredGroup` "Rust-types" the variables exactly once for each, and returns the list of
// types. The `PredGroup` may be `nullptr`. A reference to a `privateSetList` has to be given. Well, at least a reference to any `map` between a set
// name and a module name. It has to be given so that a "set type" can be recognized.
void checkAndGetTypesStrict(const std::unordered_set<const std::string*>*, const PredGroup*, std::unordered_map<std::string, const RustType*>*,
                            std::unordered_map<std::string, const std::string*>* set);

void collectTypes(const PredGroup*, std::unordered_map<std::string, const RustType*>*, std::unordered_map<std::string, const std::string*>* set);
void checkTypes(const std::unordered_set<const std::string*>*, std::unordered_map<std::string, const RustType*>*);

// Checks an abstract operation & its implementation. Set given as argument.
void checkOperations(Operation*, Operation*, std::unordered_map<std::string, const std::string*>*);

#endif
