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
// LABERR: voir si le langage est correct.

// See the `.h` files for the documentation.

#include "b2rust.h"
#include "debug.h"
#include "./parser/bxml/machine.h"


Module* b2rust::main_module;
std::unordered_map<std::string, Module> b2rust::imports;
Parser* b2rust::p_main_module;
std::unordered_map<std::string, Parser*> b2rust::p_imports;
std::unordered_set<std::string> b2rust::c_imports;
RustModule* b2rust::r_main_module;
std::unordered_map<std::string,  RustModule*> b2rust::r_imports;

int main(const int argc, const char* const* const argv) { // This one is fine.
  new Input(argc, argv);

  // We parse the BXML file.
  b2rust::p_main_module = new Parser(b2rust::main_module);
  
  // We also parse transitively imported components.
  for (const auto& [key, value] : b2rust::imports) {
    b2rust::p_imports.insert({key, new Parser(&value)});
  }

  // The parsing might already raise errors.
  if (Checker::checking_error) {
    cerr << "b2rust parsing failed! Please only input files which match the b2rust specification." << endl;
    return ERR_BXML_PARSING;
  }

  // The checking. This will recursively check other components.
  b2rust::p_main_module->checkMe();

  // If the checking failed...
  if (Checker::checking_error) {
    cerr << "b2rust checking failed! Please only input files which match the b2rust specification." << endl;
    return ERR_BXML_CHECKING;
  }

  // We convert the main module. It will recursively import the other modules.
  b2rust::r_main_module = new RustModule(b2rust::p_main_module);

  // We print the module.
  PrintAll(&b2rust::r_main_module->name, b2rust::r_main_module);
  // And also the imported components. Each of them needs its own file.
  for (const auto& [key, value] : b2rust::r_imports) {
    PrintAll(&key, value);
  }
  
  return OK;
}
