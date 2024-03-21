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
#include "r_expression.h"
#include "../util/tools.h"
#include "../debug.h"
#include "../parser/bxml/binaryexp.h"
#include "../parser/bxml/booleanliteral.h"
#include "../parser/bxml/emptyset.h"
#include "../parser/bxml/id.h"
#include "../parser/bxml/integerliteral.h"
#include "../parser/bxml/stringliteral.h"
#include "../parser/bxml/naryexp.h"
#include "../parser/bxml/select.h"
#include "../parser/expression_leaf.h"
#include "./r_module.h"
#include "./types.h"
#include "./arrayaccess.h"
#include "../parser/bxml/booleanexp.h"

#include <string>

#include <map>
#include <unordered_set>
#include <vector>

const RustExpression* Id::ConvertMe(const Context* context) const {
  return _Variable(context, value);
}


const RustExpression* IntegerLiteral::ConvertMe(const Context*) const {
  return new Int(*value);
}


const RustExpression* BooleanLiteral::ConvertMe(const Context*) const {
  return new Bool(*value);
}


const RustExpression* StringLiteral::ConvertMe(const Context*) const {
  return new RustString(*value);
}

const RustExpression* BooleanExp::ConvertMe(const Context* context) const {
  return this->predGroup->ConvertMe(context);
}


bool is_domain(const std::string target) {
  std::unordered_set<std::string> domaine = {"_i8", "_u8", "_i16", "_u16", "_i32", "_u32","_i64","_u64","_i128","_u128"};
  return domaine.count(target) > 0;
}

const RustType* to_rust_type(const std::string* op_name) {
  std::string r_op;
  if (RustType::operationAssociation.count(*op_name)>0){
      r_op = RustType::operationAssociation.at(*op_name);
  } else {
    return NULL;
  };

  std::string domain = r_op.substr(r_op.find('_') + 1);
  return RustType::types.at(domain);

}

std::string to_operator(const std::string* op_name) {
  std::string r_op;
  if (RustType::operationAssociation.count(*op_name)>0){
      r_op = RustType::operationAssociation.at(*op_name);
  } else {
    return "";
  };

  std::string operationName = r_op.substr(0, r_op.find('_'));
  std::map<std::string,std::string> assoc = {
    {"add","+i"},
    {"sub","-i"},
    {"mul","*i"},
    {"div","/i"},
    {"lshift","<<i"},
    {"rshift",">>i"},
    {"and","&i"},
    {"or","|i"},
    {"xor","^i"},
    {"pow","**i"},
    {"mod","mod"},
    {"fit","id"}
  };

  if (assoc.find(operationName)!= assoc.end()){
    return assoc.at(operationName);
  } else {
    return "";
  }
}


const RustExpression* BinaryExp::ConvertMe(const Context* context) const {
  // It is a binary expression.
  auto left = exp.at(0);
  auto right = exp.at(1);

  // either array or fonction evaluation
  if (*op == "(") {
    const Id* array = reinterpret_cast<const Id*>(left);
    std::string symb = to_operator(array->value);
    if (!symb.empty() && symb != "id") {
      const BinaryExp* operandes = reinterpret_cast<const BinaryExp*>(right);
      const std::string* p_symb = &symb;
      return new BinaryRustExpression(operandes->exp.at(0)->ConvertMe(context), p_symb, operandes->exp.at(1)->ConvertMe(context), to_rust_type(array->value));
    }
    if (!symb.empty()) {
      return right->ConvertMe(context);
    }

    auto tuple = dynamic_cast<const BinaryExp*>(right);
    if (tuple && *tuple->op == "|->"){
      auto leafs = tuple->getTupleLeafs();
      std::vector<const RustExpression*> convertedLeafs; // Pas besoin d'utiliser new ici, car nous n'avons pas besoin d'allouer dynamiquement le vecteur.

      // Utilisation de la fonction lambda avec le contexte capturé par valeur.
      std::transform(leafs->begin(), leafs->end(), std::back_inserter(convertedLeafs), [context](const Exp* exp) {
          return exp->ConvertMe(context);
      });
      return new ArrayAccess(left->ConvertMe(context),convertedLeafs);
    }
  } else if (*op == "*s"){
      //ensemble des ids representants des intervalles  ou intervalles
      auto leafs = this->getLeafs();
      RustUniformArray* result = nullptr;
      for (int i = leafs->size() -1 ; i >= 0 ; --i) {
        const Exp* leaf = leafs->at(i);
        auto leafInterval = leaf->isInterval().value();
        if (i == leafs->size() -1 ) {
            // Create the RustUniformArray and Int for the first leaf.
            result = new RustUniformArray(leafInterval->ConvertMe(context), right->ConvertMe(context));
        } else {
            // Create the RustUniformArray and Int for subsequent leaves and link them together.
            result = new RustUniformArray(leafInterval->ConvertMe(context), result);
        }
      }
      return result;

  }

  return new BinaryRustExpression(exp.at(0)->ConvertMe(context), op, exp.at(1)->ConvertMe(context));
}


const RustExpression* EmptySet::ConvertMe(const Context*) const {
  // We suppose it is an empty tabular.
  return new RustArray;
}

const RustExpression* NaryExp::ConvertMe(const Context* context) const {
  // It is a nary expression. We suppose it is a tabular instanciation. It has at least one element; if it wasn’t the case, it
  // no you can not assume this

  if(exp.size() == 1){
    auto notSingleton = dynamic_cast<const BinaryExp*>(exp.at(0));
    if (!notSingleton || (notSingleton && *notSingleton->op != "|->")){
      return exp.at(0)->ConvertMe(context);
    }
  }

  auto ra = new RustArray;

  // Ordered map for values.
  std::map<mathint_t, const RustExpression*> values;

  for (const Exp* e : exp) {
    // According to the checking, it is necessarily a `BinaryExp` whose left members are `IntegerLiteral`s.
    auto be = reinterpret_cast<const BinaryExp*>(e);
    auto il = reinterpret_cast<const IntegerLiteral*>(be->exp.at(0));

    // We add the value in the map.
    values[*il->value] = be->exp.at(1)->ConvertMe(context);
  }

  // Now, the maps contains all the interesting values.
  for (auto const& [_, v] : values) {
    ra->values.push_back(v);
  }


  return ra;
}


Int::Int(const std::string& value_s) :
  value(value_s) {
}

Int::Int(size_t n) 
: value(std::to_string(n))
{

}

Bool::Bool(const std::string& value_s) :
  value(value_s == "TRUE" ? true : false) {
}


Bool::Bool(bool value_s) :
  value(value_s) {
}




RustString::RustString(const std::string value_s) :
  value(value_s) {
}


Variable::Variable(const std::string* value, const RustType* _type) :
  name(*value), type(_type) {
}


GlobalVariable::GlobalVariable(const std::string* value, const RustType* _type) :
  Variable(value, _type) {
}


GlobalConstant::GlobalConstant(const std::string* value, const RustType* _type) :
  Variable(value, _type) {
}

LocalVariable::LocalVariable(const std::string* value, const RustType* _type) :
  Variable(value, _type) {
}

UnknownVariable::UnknownVariable(const std::string* value, const RustType* _type) :
  Variable(value, _type) {
}

ParameterVariable::ParameterVariable(const std::string* value, const RustType* _type) :
  Variable(value, _type) {
}

FieldAccess::FieldAccess(const std::string* value,std::vector<std::string>* path, const RustType* _type) :
  Variable(value, _type),
  _path(path){
}

ConstantAccess::ConstantAccess(const std::string* value, const std::string* path, const RustType* _type) :
  Variable(value, _type),
  _path(path){
}

Enumerator::Enumerator(const std::string* enumerator, const std::string* _enum, const RustType* _type) :
  Variable(enumerator,_type),
  _enum(*_enum) {
}





const Variable* _Variable(const Context* context, const std::string* value) {


  if (context->local.find(*value) != context->local.end()) {
    // It is a local variable.
    return new LocalVariable(value, (context->local.at(*value))->convertIfPartial(context));
  } else if (context->parameters.find(*value) != context->parameters.end()) {
    // It is a parameters variable.
    return new ParameterVariable(value, (context->parameters.at(*value))->convertIfPartial(context));
  } else if (context->globalVariables.find(*value) != context->globalVariables.end()) {
    // The variable is a global variable.
    return new GlobalVariable(value, (context->globalVariables.at(*value))->convertIfPartial(context));
    // It is a local variable... But is it a reference? (It is the case e.g. for input/output parameters.)
  } else if (context->globalConstants.find(*value) != context->globalConstants.end()) {
    // The variable is a global variable.
    return new GlobalConstant(value, (context->globalConstants.at(*value))->convertIfPartial(context));
    // It is a local variable... But is it a reference? (It is the case e.g. for input/output parameters.)
  }  else if (context->enumeratorsSet->count(*value)>0) {
    // Well, it must be a `SET` ! But the enum it is defined in as well as the module it is defined in have to be found.
    const std::string* the_enum = context->enumeratorsSet->at(*value);
    // We provide the module only if it is not the name of the `RustModule`.
    return new Enumerator(value, the_enum, new enumType(the_enum));
  } else if (context->variableNameAssoc.count(*value)){
      auto path = context->variableNameAssoc.at(*value);
      auto childModule = b2rust::r_imports.at(path->back().second);
      auto childContext = childModule->context;
      auto name = Tools::getLastWord(*value);
      auto var = _Variable(&childContext, &name);
      std::vector<std::string>* firstMembers = new std::vector<std::string>();
      firstMembers->reserve(path->size()); // Pour éviter les réallocations
      for (const auto& pair : *path) {
          firstMembers->push_back(pair.first);
      }

      return new FieldAccess(&name,firstMembers,var->getType());

  } else if (context->constantNameAssoc.count(*value)){
      auto mch_name = context->constantNameAssoc.at(*value);
      auto childModule = b2rust::r_imports.at(*mch_name);
      auto childContext = childModule->context;
      auto name = Tools::getLastWord(*value);
      auto var = _Variable(&childContext, &name);
      return new ConstantAccess(&name,mch_name,var->getType());

  } else {
    Report::emitWarning(fmt::format("untyped variable found: {}", *value));

    return new UnknownVariable(value,NULL);
  }

}


BinaryRustExpression::BinaryRustExpression(const RustExpression* left, const std::string* symbol, const RustExpression* right, const RustType* _resultType) :
  left_expr(left),
  right_expr(right),
  resultType(_resultType) {
  std::map<std::string, binaryExpression> assoc = {
    {"+i", addition},
    {"-i", substraction},
    {"*i", multiplication},
    {"/i", division},
    {"<<i", left_shift},
    {">>i", right_shift},
    {"|i", bitwise_or},
    {"^i", bitwise_xor},
    {"&i", bitwise_and},
    {"**i", exponentiation},
    {"mod", modulo},
    {"..", interval},
    {"(", tabularPosition},
    {"|->",tuplePosition}

  };
  type = assoc.at(*symbol);
}

BinaryRustExpression::BinaryRustExpression(const RustExpression* left, const std::string* symbol, const RustExpression* right) :
  left_expr(left),
  right_expr(right){
  std::map<std::string, binaryExpression> assoc = {
    {"+i", addition},
    {"-i", substraction},
    {"*i", multiplication},
    {"/i", division},
    {"<<i", left_shift},
    {">>i", right_shift},
    {"|i", bitwise_or},
    {"^i", bitwise_xor},
    {"&i", bitwise_and},
    {"**i", exponentiation},
    {"mod", modulo},
    {"..", interval},
    {"(", tabularPosition},
    {"|->",tuplePosition}

  };
  type = assoc.at(*symbol);
  if(type == tabularPosition){
    auto access = reinterpret_cast<const PartialTabular*>(this->left_expr->getType()); //its alright because elementstype of partialarray and crusttabular is same
    resultType = access->elementsType;
  } else {
    resultType = NULL;
  }
}



void Select::ConvertMe(const Context*, std::vector<const RustInstruction*>*) const {
  // By default, it is a non-implem thing and it should not be translated.
  Report::emit(Report::Level::FATAL, "Unexpected Select substitution");
}

RustUniformArray::RustUniformArray(const RustExpression* size_arg,  const RustExpression* value_arg) :
  size(size_arg),
  value(value_arg){

}
