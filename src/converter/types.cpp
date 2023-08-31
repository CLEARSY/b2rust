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
#include "types.h"
#include "../util/tools.h"
#include "../parser/bxml/binaryexp.h"
#include "../parser/bxml/binarypred.h"
#include "../parser/bxml/expcomparison.h"
#include "../parser/bxml/id.h"
#include "../parser/bxml/instruction.h"
#include "../parser/bxml/naryexp.h"
#include "../parser/bxml/narypred.h"
#include "../parser/bxml/predicatetype.h"
#include "../parser/bxml/unarypred.h"
#include "../parser/expression_leaf.h"
#include "arrayaccess.h"

#include <fstream>
#include <iostream>

std::map<std::string, const RustType*> RustType::types;

bool_t RustType::bool_o;
i8_t RustType::i8_o;
i16_t RustType::i16_o;
i32_t RustType::i32_o;
i64_t RustType::i64_o;
i128_t RustType::i128_o;
u8_t RustType::u8_o;
u16_t RustType::u16_o;
u32_t RustType::u32_o;
u64_t RustType::u64_o;
u128_t RustType::u128_o;
string_t RustType::string_o;
IntegerType RustType::integer_o;
ErrorType RustType::error_o;


//====================this block only consist to load b2rust_types.cfg file ===============================//
bool loadTypesFromConfig() {

  const char* envPath = std::getenv("B2RUST_CONF_HOME");

  if (envPath == nullptr) {
    std::cerr << "The environement variable of b2rust.cfg home is not defined.\n" << std::endl;
    std::cerr << "Indication : export B2RUST_CONF_HOME=\"path/to/b2rust/files/\"" << std::endl;
    Checker::checking_error = true;
  }
  std::filesystem::path configPath = std::filesystem::path(envPath) / "b2rust_types.cfg";
  configPath = Tools::expandTilde(configPath);
  
  // Path to config file
  std::ifstream file(configPath);
  if (!file.is_open()) {
    std::cerr << "Error the type file can not be opened " << std::endl;
    return false;
  }

  std::string key, value;
  while (file >> key >> value) {
    
    const RustType* rustType = nullptr;

  
    if (value == "rust_bool") {
      rustType = &RustType::bool_o;
    } else if (value == "rust_i8") {
      rustType = &RustType::i8_o;
    } else if (value == "rust_i16") {
      rustType = &RustType::i16_o;
    } else if (value == "rust_i32") {
      rustType = &RustType::i32_o;
    } else if (value == "rust_i64") {
      rustType = &RustType::i64_o;
    } else if (value == "rust_i128") {
      rustType = &RustType::i128_o;
    } else if (value == "rust_u128") {
      rustType = &RustType::u128_o;
    } else if (value == "rust_u64") {
      rustType = &RustType::u64_o;
    } else if (value == "rust_u32") {
      rustType = &RustType::u32_o;
    } else if (value == "rust_u16") {
      rustType = &RustType::u16_o;
    } else if (value == "rust_u8") {
      rustType = &RustType::u8_o;
    } else if (value == "STRING") {
      rustType = &RustType::string_o;
    }

    if (rustType != nullptr) {
      // Add the association pair, new_type rust_type
      RustType::types[key] = rustType;
    }
  }

  file.close();
  return true;
}

// Using the namespace can make this program execute before the main
namespace {
struct TypesLoader {
  TypesLoader() {
    bool success = loadTypesFromConfig();
    if (!success) {
      std::cerr << "Error: b2rust failed to load types from config file." << std::endl;
      exit(1);
    }
  }
};

//===============================================END=====================================================//



//====================this block only consist to load b2rust_operations.cfg file ===============================//
static TypesLoader typesLoader;
} // namespace

std::map<std::string, std::string> RustType::operationAssociation;

bool loadOperationAssociationFromConfig() {

  const char* envPath = std::getenv("B2RUST_CONF_HOME");

  if (envPath == nullptr) {
    std::cerr << "The environement variable of b2rust.cfg home is not defined.\n" << std::endl;
    std::cerr << "Indication : export B2RUST_CONF_HOME=\"path/to/b2rust/files/\"" << std::endl;
    Checker::checking_error = true;
  }
  std::filesystem::path configPath = std::filesystem::path(envPath) / "b2rust_operations.cfg";
  configPath = Tools::expandTilde(configPath);
  

  std::ifstream file(configPath);
  if (!file.is_open()) {
    std::cerr << "Error the op file can not be opened ." << std::endl;
    return false;
  }

  std::string key, value;
  while (file >> key >> value) {
    RustType::operationAssociation[key] = value;
  }

  file.close();
  return true;
}

namespace {
struct OperationAssociationLoader {
  OperationAssociationLoader() {
    bool success = loadOperationAssociationFromConfig();
    if (!success) {
      std::cerr << "Error: b2rust failed to load op from config file." << std::endl;
      exit(1);
    }
  }
};

static OperationAssociationLoader operationAssociationLoader;
} // namespace


//===============================================END=====================================================//



// By default, it doesn’t match the requirements.
const RustType* Exp::RightExprType(std::unordered_map<std::string, const std::string*>*) const { 
  return NULL; 
}


const RustType* Id::RightExprType(std::unordered_map<std::string, const std::string*>* sets) const {
  auto it = RustType::types.find(*value);
  if (it != RustType::types.end()) {
    // It is a recognized type!
    return it->second;
  }

  // Is it defined in a `SET` somewhere?
  if (sets->find(*value) != sets->end()) {
    return new enumType(value);
  }

  return NULL;
}

//If the rightexpr of the operation belongsTo is a binary expression, the only case possible it is an array
const RustType* BinaryExp::RightExprType(std::unordered_map<std::string, const std::string*>* set) const {

  if (exp.size() != 2) {
    return NULL;
  }

  if (*op != "-->" && *op != "*s") {
    return NULL;
  }

  // the last still needs to be verified. Well, it just needs to be a standard b2rust-recognized type, so...
  const RustType* rtype = exp.at(1)->RightExprType(set);

  if (!rtype) {
    return NULL;
  }

  // That the first `Exp` is an interval which begins by 0 and finishes with an integer >= -1.
  std::optional<const Exp*> upper = exp.at(0)->isInterval();

  if (!upper.has_value()) {
    // This is not an interval.
    auto bi_left = dynamic_cast<const BinaryExp*>(exp.at(0));
    // it may be a bunch of cartesian product
    if (bi_left && *bi_left->op == "*s") {
      auto leafs = bi_left->getLeafs();
      RustType* result = nullptr;
      for (size_t i = leafs->size(); i-- > 0;) {
        const Exp* leaf = leafs->at(i);
        auto leafInterval = leaf->isInterval().value();
        if (i == leafs->size() - 1) {
          // Create the RustUniformArray and Int for the first leaf.
          result = new PartialTabular(leafInterval, rtype);
        } else {
          // Create the RustUniformArray and Int for subsequent leaves and link them together.
          result = new PartialTabular(leafInterval, result);
        }
      }
      return result;
    }
    return NULL;
  }
  return new PartialTabular(upper.value(), rtype);
}

PartialTabular::PartialTabular(const Exp* size_arg, const RustType* type_arg)
    : size(size_arg),
      elementsType(type_arg) {}

RustTabular::RustTabular(const RustExpression* size_arg, const RustType* type_arg)
    : size(size_arg),
      elementsType(type_arg) {}

enumType::enumType(const std::string* s)
    : name(s) {}


const RustType* Int::getType() const {
  return &RustType::integer_o;
}

const RustType* Bool::getType() const {
  return &RustType::bool_o;
}

const RustType* RustString::getType() const {
  return &RustType::string_o;
}

const RustType* RustPredicate::getType() const {
  return &RustType::error_o;
}

const RustType* ArrayAccess::getType() const {
  return this->array->getType();
}

const RustType* RustUniformArray::getType() const {
  return new RustTabular(size,this->value->getType());
  }


const RustType* Enumerator::getType() const {
  return this->type;
}

const RustType* RustArray::getType() const {
  return new RustTabular(new Int(this->values.size()),this->values.at(0)->getType());
}

const RustType* BinaryRustExpression::getType() const {
  return resultType;
}

const RustType* FieldAccess::getType() const {
  return this->type;
}

const RustType* ConstantAccess::getType() const {
  return this->type;
}

const RustType* ParameterVariable::getType() const {
  return this->type;
}

const RustType* UnknownVariable::getType() const {
  return NULL;
}

const RustType* LocalVariable::getType() const {
  return this->type;
}

const RustType* GlobalVariable::getType() const {
  return this->type;
}

const RustType* GlobalConstant::getType() const {
  return this->type;
}

const RustType* RustType::convertIfPartial(const Context*) const {
  return this;
}

const RustType* PartialTabular::convertIfPartial(const Context* context) const {
  return new RustTabular(this->size->ConvertMe(context),this->elementsType->convertIfPartial(context));
}

