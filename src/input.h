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
#ifndef H_INPUT
#define H_INPUT

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string.h>
#include <tinyxml2.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "error_codes.h"

// A module is just an abstract machine and an implementation, for now.
struct Module {
  tinyxml2::XMLElement* am;
  std::vector<tinyxml2::XMLElement*>* ref = NULL;
  tinyxml2::XMLElement* impl = NULL;

  bool is_base() { return (impl == NULL); }
};

class Input {
public:
  Input(const int argc, const char* const* const argv); // This one is fine.

  // The stream where to output errors.
  static std::ostream& err;

  // A path. WITH A TRAILING SLASH!
  static std::optional<std::string> include_path;
  // Just a name without any slash. So, NOT a path.
  static std::optional<std::string> main_module_name;
  // The directory we want to input the files to. WITH A TRAILING SLASH!
  static std::optional<std::string> output_dir;

  // file that should be ignored
  static std::unordered_set<std::string> exceptions;

  // METHODS
private:
  friend std::ostream& operator<<(std::ostream& os, const Input*);
};

#endif
