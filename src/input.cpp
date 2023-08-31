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
#include "input.h"
#include "./b2rust.h"
#include "./parser/parser.h"
#include "./util/tools.h"

#include <unordered_map>

using namespace tinyxml2;
namespace fs = std::filesystem;

std::ostream& Input::err = std::cerr;
std::optional<std::string> Input::include_path;
std::optional<std::string> Input::main_module_name;
std::optional<std::string> Input::output_dir;

std::unordered_set<std::string> Input::exceptions;

//=========This block consist only to load exceptions configuration file ===========//
bool loadExceptions() {

  const char* envPath = std::getenv("B2RUST_CONF_HOME");

  if (envPath == nullptr) {
    std::cerr << "The environement variable of b2rust.cfg home is not defined.\n" << std::endl;
    std::cerr << "Indication : export B2RUST_CONF_HOME=\"path/to/b2rust/files/\"" << std::endl;
    return false;
  }
  std::filesystem::path configPath = std::filesystem::path(envPath) / "b2rust_exceptions.cfg";

  // allow the use of "~"
  configPath = Tools::expandTilde(configPath);

  std::ifstream file(configPath);
  if (!file.is_open()) {
    std::cerr << "Error the exceptions file configuration can not be opened ." << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(file, line)) {
    Input::exceptions.insert(line);
  }

  file.close();
  return true;
}

namespace {
struct ExceptionLoader {
  ExceptionLoader() {
    bool success = loadExceptions();
    if (!success) {
      std::cerr << "Error: b2rust failed to load exceptions from config file." << std::endl;
      exit(1);
    }
  }
};

static ExceptionLoader exceptionLoader;
} // namespace

//======================================END============================================//

Input::Input(const int argc, const char* const* const argv) {

  //======== First, the call code synthax should be checked=================================//

  static auto err_bad_syntax = []() {
    Input::err << "Usage: b2rust main_module_name -I modules_directory" << std::endl;
    exit(ERR_SYNTAX);
  };

  static auto option_into = [argc, argv](int* i, std::optional<std::string>* r) {
    (*i)++;
    if (*i >= argc) {
      // This is NOT fine: there’s no argument next to the option.
      err_bad_syntax();
    }
    // We shouldn’t be wanting to redefine the string.
    if (r->has_value()) {
      // It has already been defined.
      err_bad_syntax();
    }
    // Else, this is fine.
    *r = argv[*i];
  };

  // Put the parameter inside the string. Suppose the argument is well-defined.
  static auto into = [argc, argv](int* i, std::optional<std::string>* r) {
    // We shouldn’t be wanting to redefine the string.
    if (r->has_value()) {
      // It has already been defined.
      err_bad_syntax();
    }
    // Else, this is fine.
    *r = argv[*i];
  };

  static std::unordered_map<std::string, std::optional<std::string>*> actions = {{"-I", &include_path}, {"-O", &output_dir}};

  for (int i = 1; i < argc; i++) {
    if (strncmp(argv[i], "-", 1) != 0) {
      // There’s something which is not an option. So, it is the main module name.
      into(&i, &main_module_name);
      continue;
    }
    auto s = actions.find(argv[i]);
    if (s != actions.end()) {
      option_into(&i, s->second);
      continue;
    }
    // Else, this is an unknown option.
    err_bad_syntax();
  }

  // After all the parsing, the user must at least give a module name and a directory path.
  if (!(include_path.has_value() && main_module_name.has_value())) {
    err_bad_syntax();
  }

  if (!fs::exists(include_path.value())) {
    Input::err << "[b2rust] Error: b2rust did not find any bxml file, did you generate the bxml file in the right directory ? " << std::endl;
    exit(ERR_BXML_LOADING);
  }

  // If he didn’t give and `output_dir`, well, it is the current directory.
  if (!output_dir)
    output_dir = ".";

  // In all cases, with add trailing slashes (even if it makes two) to the directories.
  *include_path += "/";
  *output_dir += "/";

  //======================The synthax is good now =================================//

  //========================Load every concerning file============================//

  // map between the name of a file and it's associate xmlelement
  std::map<std::string, tinyxml2::XMLElement*> fileMap;
  // map between the name of a file and the file that it refines by
  std::map<std::string, std::string> refinementMap;
  // set of implementation file
  std::set<std::string> implementationFiles;

  // Gives an XMLElement* of the machine from the name of the component. `file` is a path.
  auto load_file = [&fileMap, &refinementMap](const std::string* file) {
    XMLDocument* const doc = new XMLDocument;
    XMLError XML_error = doc->LoadFile(file->c_str());
    if (XML_error != XML_SUCCESS) {
      Input::err << "[b2rust] Error: b2rust was asked to load the file `" << *file << "` as a XML file, but it failed. TinyXML2 said the following:\n"
                 << doc->ErrorStr() << "\nI suggest you to check if the input file exists, and if I have read permission." << std::endl;
      exit(ERR_BXML_LOADING);
    }

    // Get the abstract machine.
    XMLElement* element = doc->XMLDocument::FirstChildElement("Machine");
    if (!element) {
      Input::err << "Fatal checking_error: there’s no \"Machine\" field in the BXML file." << std::endl;
      exit(ERR_BXML_CHECKING);
    }
    std::string fileName = element->Attribute("name");
    fileMap.insert({fileName, element});
  };

  auto load_all = [&fileMap, load_file]() {
    for (const auto& entry : fs::directory_iterator(*include_path)) {
      if (entry.path().extension() == ".bxml") {
        std::string fullPath = entry.path().string();
        load_file(&fullPath);
      }
    }

    if (fileMap.empty()) {
      Input::err << "[b2rust] Error: b2rust did not find any bxml file, did you generate the bxml file in the right directory ? " << std::endl;
      exit(ERR_BXML_LOADING);
    }
  };

  auto fill_map = [&fileMap, &refinementMap, &implementationFiles]() {
    for (auto& entry : fileMap) {
      XMLElement* potentialRef = entry.second->FirstChildElement("Abstraction");
      if (potentialRef) {                                            // so actually the entry refines something
        const std::string* ref_name = Parser::GetText(potentialRef); // the name of a file who is refined by the file entry.first
        refinementMap.insert({*ref_name, entry.first});              // refinementMap.at(B) = A means the file name B is refined by file A
        std::string type = entry.second->Attribute("type");
        if (type == "implementation") {
          implementationFiles.insert(entry.first);
        }
      }
    }
  };

  load_all();
  fill_map();

  auto read_file = [&fileMap](std::string fileName) -> XMLElement* {
    if (fileMap.find(fileName) != fileMap.end()) {
      return fileMap.at(fileName);
    } else {
      return NULL;
    }
  };

  auto load_refinement = [&fileMap, &refinementMap, &implementationFiles](std::string abstractName) -> vector<XMLElement*>* {
    bool finish = false;
    auto res = new std::vector<XMLElement*>;

    std::string currentFile = abstractName;
    while (!finish && refinementMap.find(currentFile) != refinementMap.end()) {
      std::string ref_name = refinementMap.at(currentFile);
      if (implementationFiles.find(ref_name) == implementationFiles.end()) { // not an implementation
        auto ref_file = fileMap.at(ref_name);
        res->push_back(ref_file);
        currentFile = ref_name;
      } else {
        finish = true;
      }
    }
    return res;
  };

  auto load_implementation = [&fileMap, &refinementMap, &implementationFiles, read_file](std::string abstractName) -> XMLElement* {
    bool finish = false;
    XMLElement* res;

    std::string currentFile = abstractName;
    while (!finish && refinementMap.find(currentFile) != refinementMap.end()) {
      std::string ref_name = refinementMap.at(currentFile);
      if (implementationFiles.find(ref_name) == implementationFiles.end()) { // not an implementation
        currentFile = ref_name;
      } else {
        res = read_file(ref_name);
        finish = true;
        return res;
      }
    }
    return NULL;
  };

  std::string main_module_path = *include_path + *main_module_name;

  // Load the main module
  auto module = new Module;
  module->am = read_file(*main_module_name);
  module->ref = load_refinement(*main_module_name);
  module->impl = load_implementation(*main_module_name);

  // This lambda just updates the list if we provide the main XMLElement*. It is recursive.
  // Declaration first (for recursion).
  std::function<void(XMLElement*)> process_update;
  std::function<void(XMLElement*)> update_list;

  process_update = [read_file, load_refinement, &update_list, load_implementation](XMLElement* elmt) -> void {
    if (elmt) {
      for (XMLElement* machine = elmt->FirstChildElement("Referenced_Machine"); machine;
           machine = machine->NextSiblingElement("Referenced_Machine")) {
        const std::string* name = Parser::GetText(machine->FirstChildElement("Name"));
        if (Input::exceptions.find(*name) == Input::exceptions.end()) {

          // We parse the associated c  omponents --- the abstract machine & the implementation.
          Module module;
          module.am = read_file(*name);
          module.ref = load_refinement(*name);
          module.impl = load_implementation(*name);
          b2rust::imports.insert(std::pair<std::string, Module>(*name, module));

          // it may be a base module
          if (module.impl != NULL) {
            update_list(module.impl);
          } else {
            update_list(module.am);
          }
        }
      }
    }
  };

  update_list = [process_update](XMLElement* element) {
    if (element) {
      XMLElement* imports_element = element->FirstChildElement("Imports");
      XMLElement* extends_element = element->FirstChildElement("Extends");
      XMLElement* sees_element = element->FirstChildElement("Sees");
      process_update(imports_element);
      process_update(extends_element);
      process_update(sees_element);
    }
  };

  update_list(module->impl);
  b2rust::main_module = module;
}
