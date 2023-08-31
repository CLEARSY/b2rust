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
#ifndef H_B2RUST
#define H_B2RUST

#include <algorithm> 		// std::find
#include <iostream>
#include <string>
#include <cstddef>
#include <string.h>

#include "parser/bxml/machine.h"
#include "parser/bxml/machine.h"
#include "converter/r_module.h"
#include "printer/printer.h"
#include "./checker/checker.h"


// Static class which contains useful objects for translation evolution.
class b2rust {
public:
  // CONCERNING THE BXML FILES:
  // The main module.
  static Module* main_module;
  // The imports.
  static std::unordered_map<std::string, Module> imports;

  // CONCERNING THE PARSER:
  // The main module.
  static Parser* p_main_module;
  // The imports.
  static std::unordered_map<std::string, Parser*> p_imports;

  // CONCERNING THE CHECKER:
  // The list of recursively imported imports which have been checked.
  static std::unordered_set<std::string> c_imports;

  // CONCERNING THE CONVERTER:
  // The main module.
  static RustModule* r_main_module;
  // The imports.
  static std::unordered_map<std::string,  RustModule*> r_imports;
};

// `int` is argc, `char` star star are the arguments. There must be either exactly one argument, either exactly two, in the form `b2rust file.bxml -o output_file`. In the latter case, `argv` is 4.
// The first argument is the input file, the BXML file.
// The second (`output_file` in my example), if specified, is the ouput file. This is where the generated code goes. b2rust must have the rights to write to this file. If the file exists *and* is not empty, the code will be appended to the existing content of the file.
//
  
int main(const int argc, const char* const* const);		// This one is fine.

#endif
