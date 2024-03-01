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
#include "b2rust.h"
#include "parser/parser.h"
#include "util/tools.h"
#include "error_codes.h"

#include <unordered_map>
#include <tinyxml2.h>

using namespace tinyxml2;
namespace fs = std::filesystem;

std::ostream &Input::err = std::cerr;
fs::path Input::config_path;
fs::path Input::project_path;
std::unordered_set<fs::path> Input::libraries_path;
string Input::main_module_name;
fs::path Input::output_dir;
std::unordered_set<std::string> Input::exceptions;

//======================================END============================================//

Input::Input(const int argc, const char* const* const argv) {

  static const string usage = R"(
Usage:
  b2rust [-h | --help]
  b2rust [-v | --version]
  b2rust -i src [ -c cfgpath ] ( -l lib )* [ -o dst ] component
Options:
  -c, --configuration path  Sets the path to the configuration directory
  -I, -i, --include path    Sets the path to a directory containing BXML files of the main project
  -l, --library path        Sets the path to a directory containing BXML files of a library project
  -o, --output path         Sets the path to a directory where the generated Rust files are stored
  -h, --help                Display this help message and exits
  -v, --version             Displays the program version and exits

Generates Rust code from the given component, using the settings in the given configuration directory,
and the BXML files of the module and its dependencies. If the component has an implementation, the
generated code is that of this implementation. Otherwise, the component is considered that of a base
module.
)";

  static const string version = "1.0";

  string configuration;
  string project;
  std::unordered_set<string> libraries;
  string output;
  string component {};

  // Parse the command line
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-h" || arg == "--help") {
      std::cout << usage;
      exit(EXIT_SUCCESS);
    } else if (arg == "-v" || arg == "--version") {
      std::cout << version << std::endl;
      exit(EXIT_SUCCESS);
    } else if (arg == "-c" || arg == "--configuration") {
      if (i+1 == argc) {
        Input::err << "Error: missing argument for option -c/--configuration." << std::endl;
        exit(EXIT_FAILURE);
      }
      ++i;
      configuration = argv[i];
    } else if (arg == "-I" || arg == "-i" || arg == "--include") {
      if (i+1 == argc) {
        Input::err << "Error: missing argument for option -I/--include." << std::endl;
        exit(EXIT_FAILURE);
      }
      ++i;
      project = argv[i];
    } else if (arg == "-l" || arg == "--library") {
      if (i+1 == argc) {
        Input::err << "Error: missing argument for option -l/--library." << std::endl;
        exit(EXIT_FAILURE);
      }
      ++i;
      const string library = argv[i];
      libraries.insert(library);
    } else if (arg == "-o" || arg == "--output") {
      if (i+1 == argc) {
        Input::err << "Error: missing argument for option -O/--output." << std::endl;
        exit(EXIT_FAILURE);
      }
      ++i;
      output = argv[i];
    } else if (arg.at(0) == '-') {
        Input::err << "Error: unknown option " << arg << "." << std::endl
                   << usage;
        exit(EXIT_FAILURE);
    } else {
      if (!component.empty()) {
        Input::err << "Error: component argument already set to " << component << "." << std::endl;
        exit(EXIT_FAILURE);
      }
      component = arg;
    }
  }
  // Check mandatory arguments have been passed
  if (component.empty()) {
    Input::err << "Error: missing argument identifying the component to translate." << std::endl;
    exit(EXIT_FAILURE);
  }
  if (project.empty()) {
    Input::err << "Error: missing path to the directory containing BXML files of the main project." << std::endl;
    exit(EXIT_FAILURE);
  }
  // Set value for optional arguments
  // - configuration: if not passed, set from environment (mandatory)
  // - output: if not passed, current directory
  if (configuration.empty()) {
    const char *envc = std::getenv("B2RUST_CONF_HOME");
    if (nullptr == envc) {
      Input::err << "Error: no path to the configuration directory and B2RUST_CONF_HOME is not set in the environment." << std::endl;
      exit(EXIT_FAILURE);
    }
    configuration = envc;
  }
  if (output.empty()) {
    output = ".";
  }
  // Sanity checks on argument values:
  // - configuration must exist and be a directory
  // - include must exist and be a directory
  // - output must exist and be a directory
  // - every given library must exist and be a directory
  static auto check_is_dir = [](const fs::path& p) {
    if (!fs::exists(p)) {
      Input::err << "Error: " << p.string() << " does not exist." << std::endl;
      exit(EXIT_FAILURE);
    }
    if (!fs::is_directory(p)) {
      Input::err << "Error: " << p.string() << " is not a directory." << std::endl;
      exit(EXIT_FAILURE);
    }
  };
  config_path = configuration;
  check_is_dir(config_path);
  project_path = project;
  check_is_dir(project_path);
  for (const auto &str: libraries) {
    fs::path library{ str };
    check_is_dir(library);
    libraries_path.insert(library);
  }
  output_dir = output;
  check_is_dir(output_dir);

  // Global variables config_path, project_path, output_dir, libraries are now set

  // Load exceptions

  if (!loadTypesFromConfig(config_path)) {
    Input::err << "Error the types file configuration can not be opened ." << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!loadOperationAssociationFromConfig(config_path)) {
    Input::err << "Error the operations file configuration can not be opened ." << std::endl;
    exit(EXIT_FAILURE);
  }

  const std::filesystem::path exceptions_path = config_path / "b2rust_exceptions.cfg";
  std::ifstream file(exceptions_path);
  if (!file.is_open()) {
    Input::err << "Error the exceptions file configuration can not be opened ." << std::endl;
      exit(EXIT_FAILURE);
  }
  std::string line;
  while (std::getline(file, line)) {
    Input::exceptions.insert(line);
  }
  file.close();

  //========================Load every concerning file============================//

  // map between the name of a file and its associated xmlelement
  std::map<std::string, XMLElement*> XmlOfComponent;
  // map between the name of a file and the file that it refines by
  std::map<std::string, std::string> refinedBy;
  // and the reverse relation
  std::map<std::string, std::string> refines;
  // set of implementation file
  std::set<std::string> implementationFiles;

  // Gives an XMLElement* of the machine from the name of the component. `file` is a path.
  auto load_file = [&XmlOfComponent](const fs::path &file) {
    XMLDocument* const doc = new XMLDocument;
    XMLError XML_error = doc->LoadFile(file.c_str());
    if (XML_error != XML_SUCCESS) {
      Input::err << "[b2rust] Error: b2rust was asked to load the file `" << file.string() << "` as a XML file, but it failed." << std::endl
                 << doc->ErrorStr() << std::endl
                 << "Check if the input file exists and is readable." << std::endl;
      exit(ERR_BXML_LOADING);
    }

    // Get the abstract machine.
    XMLElement* element = doc->XMLDocument::FirstChildElement("Machine");
    if (!element) {
      Input::err << "Fatal checking_error: there’s no \"Machine\" field in the BXML file." << std::endl;
      exit(ERR_BXML_CHECKING);
    }
    std::string fileName = element->Attribute("name");
    XmlOfComponent.insert({fileName, element});
  };

  // loads all BXML files and fill the XmlOfComponent map
  for (const auto& entry : fs::directory_iterator(project_path)) {
    if (entry.path().extension() == ".bxml") {
      load_file(entry.path());
    }
  }
  for (const auto& library_path: libraries_path) {
    for (const auto& entry : fs::directory_iterator(library_path)) {
      if (entry.path().extension() == ".bxml") {
        load_file(entry.path());
      }
    }
  }

  if (XmlOfComponent.empty()) {
    Input::err << "[b2rust] Error: b2rust did not find any bxml file, did you generate the bxml file in the right directory ? " << std::endl;
    exit(ERR_BXML_LOADING);
  }

  for (const auto& entry : XmlOfComponent) {
    string comp = entry.first;
    XMLElement *xml = entry.second;
    const XMLElement* abstraction = xml->FirstChildElement("Abstraction");
    if (nullptr != abstraction) {
      string absName{abstraction->GetText()};               // so actually the entry refines something
      refinedBy.insert({absName, comp});// refinedBy.at(B) = A means the file name B is refined by file A
      refines.insert({comp, absName});
      const std::string type = xml->Attribute("type");
      if (type == "implementation") {
        implementationFiles.insert(comp);
      }
    }
  }

  auto read_file = [&XmlOfComponent](const std::string &fileName) -> XMLElement* {
    if (XmlOfComponent.find(fileName) != XmlOfComponent.end()) {
      return XmlOfComponent.at(fileName);
    } else {
      return NULL;
    }
  };

  auto load_refinement = [&XmlOfComponent, &refinedBy, &implementationFiles](const std::string &abstractName) -> vector<XMLElement*>* {
    bool finish = false;
    auto res = new std::vector<XMLElement*>;

    std::string currentFile = abstractName;
    while (!finish && refinedBy.find(currentFile) != refinedBy.end()) {
      std::string ref_name = refinedBy.at(currentFile);
      if (implementationFiles.find(ref_name) == implementationFiles.end()) { // not an implementation
        auto ref_file = XmlOfComponent.at(ref_name);
        res->push_back(ref_file);
        currentFile = ref_name;
      } else {
        finish = true;
      }
    }
    return res;
  };

  auto load_implementation = [&XmlOfComponent, &refinedBy, &implementationFiles, read_file](std::string abstractName) -> XMLElement* {
    bool finish = false;
    XMLElement* res;

    std::string currentFile = abstractName;
    while (!finish && refinedBy.find(currentFile) != refinedBy.end()) {
      std::string ref_name = refinedBy.at(currentFile);
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

  string module_name; // name of the module to be translated
  {
    module_name = component;
    auto it = refines.find(module_name);
    while (it != refines.end()) {
      module_name = it->second;
      it = refines.find(module_name);
    }
  }

  auto module = new Module;
  module->am = read_file(module_name);
  module->ref = load_refinement(module_name);
  module->impl = load_implementation(module_name);

  // This lambda just updates the list if we provide the main XMLElement*. It is recursive.
  // Declaration first (for recursion).
  std::function<void(XMLElement*)> process_update;
  std::function<void(XMLElement*)> update_list;

  process_update = [read_file, load_refinement, &update_list, load_implementation](XMLElement* clause) -> void {
    if (nullptr == clause) {
      return;
    }
    for (XMLElement* machine = clause->FirstChildElement("Referenced_Machine");
          nullptr != machine;
          machine = machine->NextSiblingElement("Referenced_Machine")) {
      const std::string name = machine->FirstChildElement("Name")->GetText();
      if (Input::exceptions.find(name) != Input::exceptions.end()) {
        continue;
      }

      // We parse the associated components --- the abstract machine & the implementation.
      Module module;
      module.am = read_file(name);
      module.ref = load_refinement(name);
      module.impl = load_implementation(name);
      b2rust::imports.insert(std::pair<std::string, Module>(name, module));
      if (nullptr == module.impl) {
        update_list(module.am);
      } else {
        update_list(module.impl);
      }
    }
  };

  update_list = [process_update](XMLElement* element) {
    if (nullptr == element)
      return;
    process_update(element->FirstChildElement("Imports"));
    process_update(element->FirstChildElement("Extends"));
    process_update(element->FirstChildElement("Sees"));
  };

  update_list(module->impl);
  b2rust::main_module = module;
}
