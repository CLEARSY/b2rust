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
#include "parser.h"
#include "./bxml/id.h"
#include "./bxml/machine.h"
#include "../util/report.h"

#include<fmt/format.h>

bool Parser::checking_error = false;
std::string Parser::uncompliant = "Error: it seems your input files are not BXML 1.0 compliant.\n";
std::string Parser::nonTranslatableYet = "Error: it seems you used an instruction which is not translatable by b2rust yet.\n";

Parser::Parser() {}

Parser::Parser(const Module* const module) {
  am = new Machine(module->am);
  if (module->ref != NULL) {
    auto res = new std::vector<Machine*>;
    for (size_t i = 0; i < (module->ref->size()); i++) {
      Machine* mch = new Machine(module->ref->at(i));
      res->push_back(mch);
    }
    ref = res;
  } else {
    ref = NULL;
  };
  impl = (module->impl) ? new Machine(module->impl) : NULL;
}

// --- FONCTION WORKING ON ATTRIBUTES

// ------ Attribute checking functions.

// --- FONCTIONS WORKING ON NODES

// Definition of:
// -- NodeActionforeachpresent,
// -- NodeActionForEach,
// -- NodeAction
// see `.tcc` file.

void Parser::workOnAttributes(XMLElement* const element, attributeActions* actions, const std::string) {
  for (const XMLAttribute* attr = element->FirstAttribute(); attr != NULL; attr = attr->Next()) {
    auto it = actions->find(attr->Name());
    if (it == actions->end()) {
      Report::emitError(fmt::format("forbidden attribute {} for BXML element {}", attr->Name(), element->Name()));
      checking_error = true;
    } else {
      std::string str = attr->Value();
      if (std::holds_alternative<const std::string**>(it->second)) {
        *std::get<const std::string**>(it->second) = new std::string(str);
      } else if (std::holds_alternative<const bool**>(it->second)) {
        const bool* cv = str == "TRUE" ? new bool(true) : new bool(false);
        *std::get<const bool**>(it->second) = cv;
      } else if (std::holds_alternative<const unsigned**>(it->second)) {
        *std::get<const unsigned**>(it->second) = new unsigned(std::stoi(str));
      } else if (std::holds_alternative<const binaryPredOp**>(it->second)) {
        *std::get<const binaryPredOp**>(it->second) = _binaryPredOp(&str);
      } else {
        Report::fatalError(fmt::format("forbidden attribute {} for BXML element {}", attr->Name(), element->Name()),
                          EXIT_FAILURE);
      }
    }
  }
}

// Gets the text, throws an error if the first child of the element isn’t a `XMLText`.
const std::string* Parser::GetText(XMLElement* const element) {
  const char* const text = element->GetText(); // This one is fine.
  return new std::string(text);
}

const std::unordered_set<const std::string*>* Parser::getConcreteConstants() const {
  auto set = new std::unordered_set<const std::string*>;

  if (am->concreteConstants) {
    for (const Id* id : am->concreteConstants->id) {
      set->insert(id->value);
    }
  }

  if (impl) {
    if (impl->concreteConstants) {
      for (const Id* id : impl->concreteConstants->id) {
        set->insert(id->value);
      }
    }
  }
  if (ref) {

    for (size_t i = 0; i < ref->size(); i++) {
      if (ref->at(i)->concreteConstants) {
        for (const Id* id : ref->at(i)->concreteConstants->id) {
          set->insert(id->value);
        }
      }
    }
  }
  return set;
}

const std::unordered_set<const std::string*>* Parser::getConcreteVariables() const {
  auto set = new std::unordered_set<const std::string*>;

  if (am->concreteVariables) {
    for (const Id* id : am->concreteVariables->id) {
      set->insert(id->value);
    }
  }

  if (impl) {
    if (impl->concreteVariables) {
      for (const Id* id : impl->concreteVariables->id) {
        set->insert(id->value);
      }
    }
  }
  if (ref) {

    for (size_t i = 0; i < ref->size(); i++) {
      if (ref->at(i)->concreteVariables) {
        for (const Id* id : ref->at(i)->concreteVariables->id) {
          set->insert(id->value);
        }
      }
    }
  }
  return set;
}

const std::unordered_set<const std::string*>* Parser::getParametersDeclaration() const {
  auto set = new std::unordered_set<const std::string*>;
  // am is enought because all machine in the module must have the same parameters,
  // I choose am because it surely exist
  if (am->parameters) {
    for (const Id* id : am->parameters->id) {
      set->insert(id->value);
    }
  }
  return set;
}
