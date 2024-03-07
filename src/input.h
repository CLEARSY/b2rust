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
#include <string>
#include <unordered_set>
#include <vector>

namespace tinyxml2 {
  class XMLElement;
};

// A module is just an abstract machine and an implementation, for now.
struct Module {
  tinyxml2::XMLElement* am;
  std::vector<tinyxml2::XMLElement*>* ref = nullptr;
  tinyxml2::XMLElement* impl = nullptr;

  bool is_base() { return (impl == nullptr); }
};

///@todo make a namespace, not a class
class Input {
public:
  Input(const int argc, const char* const* const argv); // This one is fine.

  // The stream where to output errors.
  static std::ostream& err; ///@todo no need to alias std::cerr

  /// @brief the path of the directory containing configuration files.
  static std::filesystem::path config_path;

  /// @nbrief paths of the directory containing BXML files of the main project
  static std::filesystem::path project_path;

  /// @nbrief paths of the directories containing BXML files of library projects
  static std::unordered_set<std::filesystem::path> libraries_path;

  // Just a name without any slash. So, NOT a path.
  static std::string main_module_name;

  // The directory we want to output the files to. WITH A TRAILING SLASH!
  static std::filesystem::path output_dir;

  // file that should be ignored
  static std::unordered_set<std::string> exceptions;

  // output messages are either raw text or are structured in XML elements
  static bool xmlOutput;

  // METHODS
private:
  friend std::ostream& operator<<(std::ostream& os, const Input*);
};

#endif
