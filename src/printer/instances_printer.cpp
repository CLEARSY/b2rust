#include "instances_printer.h"
#include "../util/report.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <fmt/format.h>

using std::string;

const string InstancesPrinter::INSTANCES_FILENAME = "____Instances____.rs";

const string InstancesPrinter::getModuleName() {
  // Returning the file name without the .rs extension
  return INSTANCES_FILENAME.substr(0, INSTANCES_FILENAME.size() - 3);
}

string InstancesPrinter::getContainerGetterName(std::string type) {
  return "get_container_" + type;
}

string InstancesPrinter::getGetterName(std::string instance) {
  return "get_" + instance;
}

string InstancesPrinter::getInstancesGetterName(std::string type) {
  return "get_" + type;
}

string InstancesPrinter::getConstructorName(std::string type) {
  return "instanciate_" + type;
}

void InstancesPrinter::addModule(Context &context) {
  for (const auto &[instance, type] : context.machineTypeAssoc) {
    if (std::find(m_type_to_instances[type].cbegin(),
                  m_type_to_instances[type].cend(),
                  instance) == m_type_to_instances[type].cend()) {
      m_type_to_instances[type].push_back(instance);
      m_type_to_struct[type] = "____" + type + "____Instances____Container____";
    }
  }
}

void InstancesPrinter::print(std::ostream &stream) {
  if (not m_type_to_instances.empty()) {
    printUses(stream);
    printStructs(stream);
  }
}

void InstancesPrinter::print(string directory) {
  string path = directory + INSTANCES_FILENAME;
  std::ofstream file(path);
  if (file.is_open()) {
    print(file);
    file.close();
  } else {
    Report::fatalError(fmt::format("Error writin to file {}", path), ERR_OUTPUT_FILE);
  }
}

void InstancesPrinter::printSeparationInComment(std::ostream &stream) {
  stream << "/*" << std::endl << m_separator << "*/" << std::endl;
}

void InstancesPrinter::printCommentHeader(std::ostream &stream,
                                          std::string comment) {
  int diff = m_separator.size() - comment.size();
  string blank_spaces_to_add = string(std::max(diff, 0) / 2, ' ');
  stream << "/*" << std::endl
         << m_separator << blank_spaces_to_add << comment << blank_spaces_to_add
         << std::endl
         << m_separator << "*/" << std::endl;
}

void InstancesPrinter::printUses(std::ostream &stream) {
  stream << "use std::sync::{Arc, RwLock, OnceLock};" << std::endl << std::endl;

  for (const auto &[type, _] : m_type_to_instances) {
    stream << "use " << type << "::" << type << ";" << std::endl;
  }

  stream << std::endl;
}

void InstancesPrinter::printStructs(std::ostream &stream) {
  for (const auto &[type, instances] : m_type_to_instances) {
    printCommentHeader(stream, "The instances of " + type);
    // Printing the definition
    stream << "#[derive(Clone)]" << std::endl
           << "pub struct " << m_type_to_struct[type] << " {" << std::endl;

    for (const auto &instance : instances) {
      stream << m_indent << instance << ": Arc<RwLock<" << type << ">>,"
             << std::endl;
    }

    stream << "}" << std::endl << std::endl;

    // Printing the implementation
    stream << "impl " << m_type_to_struct[type] << " {" << std::endl << std::endl;
    printConstructor(stream, type);
    stream << std::endl;
    printGetters(stream, type);
    stream << "}" << std::endl << std::endl;
    printSeparationInComment(stream);
  }

  // Printing all the needed functions to use the vectors of instances
  printStaticGetters(stream);
  printInstancesConstructor(stream);
  printInstancesGetter(stream);
}

void InstancesPrinter::printConstructor(std::ostream &stream,
                                        std::string type) {
  stream << m_indent << "// The constructor of the container of all the "
         << type << " instances" << std::endl
         << m_indent << "fn new(id: usize) -> Self {" << std::endl
         << m_indent << m_indent << "let instance = " << m_type_to_struct[type]
         << " {" << std::endl;

  for (const auto &instance : m_type_to_instances[type]) {
    stream << m_indent << m_indent << m_indent << instance
           << ": Arc::new(RwLock::new(" << type << "::new(id)))," << std::endl;
  }

  stream << m_indent << m_indent << "};" << std::endl
         << m_indent << m_indent << "instance" << std::endl
         << m_indent << "}" << std::endl;
}

void InstancesPrinter::printGetters(std::ostream &stream, std::string type) {
  if (m_type_to_instances[type].size() > 1)
    stream << m_indent << "// The getters of the " << type << " container";
  else
    stream << m_indent << "// The getter of the " << type << " container";

  for (const auto &instance : m_type_to_instances[type]) {
    stream << std::endl
           << m_indent << "pub fn " << getGetterName(instance)
           << "(&self) -> Arc<RwLock<" << type << ">> {" << std::endl
           << m_indent << m_indent << "self." << instance << ".clone()" << std::endl
           << m_indent << "}" << std::endl;
  }
}

void InstancesPrinter::printStaticGetters(std::ostream &stream) {
  printCommentHeader(
      stream,
      "The getters of the vectors containing all the instances of "
      "the imported and seen machines");
  for (const auto &[type, instance] : m_type_to_instances) {
    string static_list;
    for (auto c : type) static_list += toupper(c);
    static_list += "_INSTANCES";

    stream << "fn " << getContainerGetterName(type)
           << "() -> &'static RwLock<Vec<" << m_type_to_struct[type] << ">> {"
           << std::endl
           << m_indent << "static " << static_list << ": "
           << "OnceLock<RwLock<Vec<" << m_type_to_struct[type]
           << ">>> = OnceLock::new();" << std::endl
           << m_indent << static_list
           << ".get_or_init(|| RwLock::new(Vec::new()))" << std::endl
           << "}" << std::endl
           << std::endl;
  }
  printSeparationInComment(stream);
}

void InstancesPrinter::printInstancesConstructor(std::ostream &stream) {
  printCommentHeader(stream, "The constructors to call in the base module");

  for (const auto &[type, _] : m_type_to_instances) {
    string vec = getContainerGetterName(type) + "().write().unwrap()";
    stream << "pub fn " << getConstructorName(type) << "() -> usize {" << std::endl
           << m_indent << "let id = " << vec << ".len();" << std::endl
           << m_indent << "let new_instances = " << m_type_to_struct[type]
           << "::new(id);" << std::endl
           << m_indent << vec << ".push(new_instances);" << std::endl
           << m_indent << "id" << std::endl
           << "}" << std::endl
           << std::endl;
  }

  printSeparationInComment(stream);
}

void InstancesPrinter::printInstancesGetter(std::ostream &stream) {
  printCommentHeader(stream, "The getters of the instances containers");

  for (const auto &[type, _] : m_type_to_instances) {
    stream << "pub fn " << getInstancesGetterName(type) << "(id: usize) -> "
           << m_type_to_struct[type] << "{" << std::endl
           << m_indent << "match " << getContainerGetterName(type)
           << "().read().unwrap().get(id).clone() {" << std::endl
           << m_indent << m_indent << "Some (instances) => instances.clone(),"
           << std::endl
           << m_indent << m_indent
           << "_ => panic!(\"Error while trying to access a non existing "
              "instance of "
           << m_type_to_struct[type] << "\")" << std::endl
           << m_indent << "}" << std::endl
           << "}" << std::endl
           << std::endl;
  }

  printSeparationInComment(stream);
}
