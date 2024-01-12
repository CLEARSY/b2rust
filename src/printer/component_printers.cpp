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
#include <string>
#include <iostream>
#include <fstream>

#include "../converter/r_module.h"
#include "../converter/r_assignement.h"
#include "../converter/r_if.h"
#include "../converter/declaration.h"
#include "../converter/function.h"
#include "../converter/functioncall.h"
#include "../converter/r_while.h"
#include "../converter/match.h"
#include "../converter/delegatecall.h"
#include "../converter/arrayaccess.h"
#include "instances_printer.h"

using namespace std;


// Header.
// Just to print several instructions.
std::string _PrintMe(std::vector<const RustInstruction*>*);



std::string RustModule::PrintMe() const {
  // TODO: manage the test script so that the newlines don’t count.
  string output;
  // We start with the `mod`s.
  if (!mods.empty()) {
    for (const std::string* m : mods) {
      // m should be defined.
      output += "mod "+*m+";\n";
    }
    output += "\n\n";
  }

  // The `use`s.
  if (!uses.empty()) {
    for (const std::string* u : uses) {
      // u should be defined.
      output+="use "+*u+";\n";
    }
    output += "\n\n";
  }

  // The `pub use`s.
  if (!pubUses.empty()) {
    for (const std::string* pu : pubUses) {
      // pu should be defined.
      output+="pub use "+*pu+";\n";
    }
    output += "\n\n";
  }

  output += "use std::convert::TryFrom;\n";
  if (not instances.empty()) {
      output += "use std::sync::{RwLock, Arc};\n";
      output += name == Input::main_module_name ?
                  "use " + InstancesPrinter::getModuleName() + "::*;\n\n":
                  "use " + InstancesPrinter::getModuleName() + ";\n";
  }
  output += "\n";


  // The enums.
  if (!enums.empty()) {
    for (auto pair : enums) {
      if (!pair.second.empty()){
        output += "#[derive(Clone, Copy, Default, Debug, Eq, PartialEq)]\n";
      } else {
        output += "#[derive(Clone, Copy, Debug, Eq, PartialEq)]\n";
      }
      output += "pub enum " + pair.first + " {\n";
      // The first one is marked as default.
      if (!pair.second.empty())
       output += "#[default]\n";

      for (std::string str : pair.second) {
          output += str + ",\n";
      }
      output += "}\n\n";
    }
  }

  // The variables & imports are printed inside a struct.
  output += "pub struct " + name + " {\n";

  // We start by the imports... For no specific reason. (Well, in the BXML specification, the `IMPORTS` clause is before any variable/constants clause.)
  if (!instances.empty()) {
    output += "// Instances of imported modules.\n";
    for (const auto& [first, second] : instances) {
      output +="pub " + *first+": Arc<RwLock<"+*second+"::"+*second+">>,\n";
    }
    if (!variables.empty()) {
      output += "\n";
    }
  }


  if (!parameters.empty()) {
    output += "// Parameters.\n";
    for (std::map<std::string, const RustType*>::const_iterator it = parameters.begin(); it != parameters.end(); ++it) {
      if (it->second) {
      output += "r#" + it->first + ": " + it->second->PrintMe() + ",\n";
      } else {
        output += "//r#" + it->first + ": " + "TODO" + ",\n";
      }
    }
  }


  if (!variables.empty()) {
    output += "// Concrete variables.\n";
    for (std::map<std::string, const RustType*>::const_iterator it = variables.begin(); it != variables.end(); ++it) {
      if (it->second) {
      output += "pub r#" + it->first + ": " + it->second->PrintMe() + ",\n";
      } else {
        output += "//pub r#" + it->first + ": " + "TODO" + ",\n";
      }
    }
  }
  output += "}\n\n";

  // The default trait is implemented only if it is the main module and it has no parameter
  if (name == Input::main_module_name && parameters.empty()) {
      output += "impl Default for " + name + "{\n";
      output += "   fn default() -> Self {\n";

      // Instanciating the needed machines
      if (not instances.empty())
        output += "let id = ";
      for (const auto& [_, type] : instances) {
          output += InstancesPrinter::getModuleName() + "::" + InstancesPrinter::getConstructorName(*type) + "();\n";
      }

      output += "     let mut instance = Self {\n";



      // We start by the imports initialisation.
      if (!instances_init.empty()) {
        output += "// Instances of imported modules initialization.\n";
        for (const auto& [instance, type] : instances) {
          output += *instance + ": " + InstancesPrinter::getModuleName() + "::" +
                  InstancesPrinter::getGetterName(*type) + "(id)." +
                  InstancesPrinter::getInstancesGetterName(*instance) + "(),";
        }
      }

      for (std::map<std::string, const RustType*>::const_iterator it = variables.begin(); it != variables.end(); ++it) {
        if (it->second) {
          output += "r#" + it->first + " : " +  it->second->PrintMeDefault() + ",\n";
        } else {
           output += "//r#" + it->first + " : Default::default(),\n";
        }
      }


      output += "\n};\n";
      output += "instance.initialisation();\n";
      output += "instance";
      output += "\n}\n}\n";
  }

  output += "impl " + name + " {\n";

  if (name != Input::main_module_name) {
      // There is at least a constructor and an initialisation.

      output += "   pub fn new(id: usize) -> Self {\n";

      // Instanciating the needed machines
      for (const auto& [_, type] : instances) {
          output += InstancesPrinter::getModuleName() + "::" + InstancesPrinter::getConstructorName(*type) + "();\n";
      }

      output += "     let mut instance = Self {\n";



      // We start by the imports initialisation.
      if (!instances_init.empty()) {
        output += "// Instances of imported modules initialization.\n";
        for (const auto& [instance, type] : instances) {
          output += *instance + ": " + InstancesPrinter::getModuleName() + "::" +
                  InstancesPrinter::getGetterName(*type) + "(id)." +
                  InstancesPrinter::getInstancesGetterName(*instance) + "(),";
        }
      }

      for (std::map<std::string, const RustType*>::const_iterator it = parameters.begin(); it != parameters.end(); ++it) {
        if (it->second) {
          output += "r#" + it->first + " : " +  it->second->PrintMeDefault() + ",\n";
        } else {
           output += "//r#" + it->first + " : Default::default(),\n";
        }
      }

      for (std::map<std::string, const RustType*>::const_iterator it = variables.begin(); it != variables.end(); ++it) {
        if (it->second) {
          output += "r#" + it->first + " : " +  it->second->PrintMeDefault() + ",\n";
        } else {
           output += "//r#" + it->first + " : Default::default(),\n";
        }
      }


      output += "\n};\n";
      output += "instance.initialisation();\n";
      output += "instance";
      output += "\n}\n\n";
  }

  std::string eventualComment = ((impl)? "" : "//");

  if(impl){
    if (!values.empty()) {
        output += "// Constant’s `VALUES`.\n";
      for (const RustInstruction* instruction : values) {
          output += eventualComment+ reinterpret_cast<const Declaration*>(instruction)->PrintMeInit();
        }
    }
  } else {

      if (!constants.empty()) {
        output += "// Constant’s `VALUES`.\n";
        output += "/* \n";
        for (std::map<std::string, const RustType*>::const_iterator it = constants.begin(); it != constants.end(); ++it) {
          if (it->second) {
            output += "pub const r#" + it->first + " : " +  it->second->PrintMe() + " = TODO;\n";
          } else {
            output += "//pub const r#" + it->first + " : TODO = TODO" + "\n";
          }
       }
       output += "*/ \n";
    }
  }




  if (!parameters.empty()){
    // If it is the main module, new does not exist
    bool is_main_module = name == Input::main_module_name;
    output += is_main_module ? "pub fn new(" : "pub fn set_parameters(&mut self,";

    for (const auto& [para, type]: parameters){
      auto newParameter ="r#" + para + "_arg";
      output  += newParameter + " : " + type->PrintMe() + ", ";
    }
    output += ")";

    if (is_main_module) {
        output += " -> Self {\n ";
        // Instanciating the needed machines
        if (not instances.empty())
          output += "let id = ";
        for (const auto& [_, type] : instances) {
            output += InstancesPrinter::getModuleName() + "::" + InstancesPrinter::getConstructorName(*type) + "();\n";
        }
        output += "let mut instance = Self { \n";
    }
    else
        output += " {\n";

    string prefix = is_main_module ? "r#" : "self.r#";
    string op = is_main_module ? " : " : " = ";
    string delim = is_main_module ? ",\n" : ";\n";

    for (std::map<std::string, const RustType*>::const_iterator it = parameters.begin(); it != parameters.end(); ++it) {
      if (it->second) {
        output += prefix + it->first + op +  "r#" + it->first +"_arg" + delim;
      } else {
         output += "//" + prefix + it->first + op + "Default::default()" + delim;
      }
    }


    for (std::map<std::string, const RustType*>::const_iterator it = variables.begin(); it != variables.end(); ++it) {
      if (it->second) {
        output += prefix + it->first + op + it->second->PrintMeDefault() + delim;
      } else {
        output += prefix + it->first + op + "Default::default()" + delim;
      }
    }

    if (is_main_module and !instances_init.empty()) {
      output += "// Instances of imported modules initialization.\n";
      for (const auto& [instance, type] : instances) {
        output += *instance + ": " + InstancesPrinter::getModuleName() + "::" +
                InstancesPrinter::getGetterName(*type) + "(id)." +
                InstancesPrinter::getInstancesGetterName(*instance) + "(),";
      }
    }

  if (is_main_module)
      output += "};\n"
                "instance.initialisation();"
                "instance";
  else
    output += "self.initialisation();\n";
  output += "}\n";

  }



  //private method
  output += "fn initialisation(&mut self) {\n";

  if (!instances.empty()) {

    output += "// Instances of imported modules.\n";
    for (const auto& [renamed, machineName] : instances) {
      if(instancesArguments.find(renamed) != instancesArguments.end()){
        output += "self." + *renamed + ".write().unwrap().set_parameters(";
        for (const auto arg : instancesArguments.at(renamed)) {
            output += arg->PrintMe() + ", ";
        }
        output.pop_back();
        output.pop_back();
        output += ");\n";
      }
    }

  }

  if (!initialisations.empty()) {
    // We continue with the values.
    output += "// `INITIALISATION` clause.\n";
    for (const RustInstruction* instruction : initialisations) {
      output += eventualComment + instruction->PrintMe();
    }
  }
  output += "}\n";

  // The functions.
   for (Function const* function : functions)
    output += function->PrintMe(impl == NULL);

  output += "}\n";

  // No `main` is printed (we generate a library).

  return output;
}


string Function::PrintMe() const {
  std::string entete = (prive)? "" : "pub ";
  std::string output = "\n" + entete + "fn "+name+"(&mut self";

  // The input parameters.
  for (auto const& [key, value] : inputParameters) {
    output += ", r#" + key + ": &" + value->PrintMe();
  }
  // The output parameters.
  for (auto const& [key, value] : outputParameters) {
    output += ", r#" + key + ": &mut " + value->PrintMe();
  }
  output += ") {\n";

  // Print the instructions.
  for (const RustInstruction* instruction : instructions) {
    output += instruction->PrintMe();
  }

  return output += "}\n";
}


std::string RustIf::PrintMe() const {
  std::string str = "if "+predicate->PrintMe()+" {\n" + _PrintMe(then_instr) + "}";

  // The else might not be printed.
  if (!else_instr->empty()) {
    str += " else {\n" + _PrintMe(else_instr) + "}";
  }
  str += "\n";
  return str;
}

string Function::PrintMe(bool am) const {
  if (!am) {
    return PrintMe();
  } else {
    std::string output = "\npub fn " + name + "(&mut self";

    // The input parameters.
    for (auto const& [key, value] : inputParameters) {
      output += ", r#" + key + ": &" + value->PrintMe();
    }
    // The output parameters.
    for (auto const& [key, value] : outputParameters) {
      output += ", r#" + key + ": &mut " + value->PrintMe();
    }
    output += ") {\n";
    output += "unimplemented!(\"" + name +" is unimplemented\");\n" ;
    output += "}\n";
    return output;
  }
}


std::string RustAssignement::PrintMe() const {
  if (dynamic_cast<const RustTabular*>(leftExpression->getType())){
    return leftExpression->PrintMe()+" = "+rightExpression->PrintMe() + ";\n";
  } else if (dynamic_cast<const Int*>(rightExpression)){
    auto val = dynamic_cast<const Int*>(rightExpression);
    if (val->value > 2147483647 || val->value < -2147483648){
      return leftExpression->PrintMe()+" = "+leftExpression->castToType(rightExpression) +";\n";
    }
  }
  //return leftExpression->PrintMe()+" = ("+rightExpression->PrintMe()+ ") "+leftExpression->castToType() +";\n";
  return leftExpression->PrintMe()+" = " + leftExpression->getType()->PrintMe()+"::try_from"+ "("+rightExpression->PrintMe()+ ").unwrap();\n";
}


std::string RustAssignement::PrintMeInit() const {
  auto l_expr = dynamic_cast<const GlobalVariable*>(leftExpression);
  if (l_expr){
      return l_expr->PrintMeInit()+" : "+rightExpression->PrintMe()+",\n";
  } else{
    return PrintMe();
  }
}

std::string RustAssignement::PrintMeInit2() const {
  auto l_expr = dynamic_cast<const GlobalVariable*>(leftExpression);
  if (l_expr){
      return l_expr->PrintMeInit() + " : Default::default(),\n" ;
  } else{
    return PrintMe();
  }
}

// TODO: define a SimpleType class whose PrintType only prints the value?
// It has to be changed; these fonctions are used to print the constants but it is used by the debugger to print just an expression, which can be misleading.
// string Int::PrintType() const {
//   return "i32";
// }

std::string i128_t::PrintMe() const {
  return "i128";
}

std::string i128_t::PrintMeDefault() const {
  return "i128::default()";
}

std::string i64_t::PrintMe() const {
  return "i64";
}

std::string i64_t::PrintMeDefault() const {
  return "i64::default()";
}

std::string i32_t::PrintMe() const {
  return "i32";
}

std::string i32_t::PrintMeDefault() const {
  return "i32::default()";
}

std::string i16_t::PrintMe() const {
  return "i16";
}

std::string i16_t::PrintMeDefault() const {
  return "i16::default()";
}

std::string i8_t::PrintMe() const {
  return "i8";
}

std::string i8_t::PrintMeDefault() const {
  return "i8::default()";
}

std::string u128_t::PrintMe() const {
  return "u128";
}

std::string u128_t::PrintMeDefault() const {
  return "u128::default()";
}

std::string u64_t::PrintMe() const {
  return "u64";
}

std::string u64_t::PrintMeDefault() const {
  return "u64::default()";
}

std::string u32_t::PrintMe() const {
  return "u32";
}

std::string u32_t::PrintMeDefault() const {
  return "u32::default()";
}

std::string u16_t::PrintMe() const {
  return "u16";
}

std::string u16_t::PrintMeDefault() const {
  return "u16::default()";
}

std::string u8_t::PrintMe() const {
  return "u8";
}


std::string u8_t::PrintMeDefault() const {
  return "u8::default()";
}

std::string bool_t::PrintMe() const {
  return "bool";
}

std::string bool_t::PrintMeDefault() const {
  return "bool::default()";
}

std::string string_t::PrintMe() const {
  return "str";
}

std::string string_t::PrintMeDefault() const {
  return "error";
}

std::string PartialTabular::PrintMe() const {
  return "partial tabular printer should never be call";
}

std::string PartialTabular::PrintMeDefault() const{
  return "partial tabular default printer should never be call";
}

std::string RustTabular::PrintMe() const {
  return "[" + elementsType->PrintMe() + "; (" + size->PrintMe() +  " + 1) as usize ]";
}

std::string RustTabular::PrintMeDefault() const{
  return "[" + elementsType->PrintMeDefault() + "; (" + size->PrintMe() +  " + 1) as usize]";
}

string Int::PrintMe() const {
  return value.str();
}

string RustString::PrintMe() const {
  return "\" " + value + " \"";
}


// string Bool::PrintType() const {
//   return "bool";
// }


string Bool::PrintMe() const {
  return value == true ? "true" : "false";
}


// string GlobalVariable::PrintType() const {
//   return "You shouldn’t be reading this. It is a b2rust bug.";
// }


string GlobalVariable::PrintMe() const {
  return "self.r#"+name;
}

string GlobalVariable::PrintMeInit() const {
  return "r#"+name;
}

string GlobalConstant::PrintMe() const {
  return "Self::r#"+name;
}



string LocalVariable::PrintMe() const {
  return "r#"+name;
}

string UnknownVariable::PrintMe() const {
  return "//*r#"+name + ": TODO ";
}

string ParameterVariable::PrintMe() const {
  return "*r#"+name;
}


string FieldAccess::PrintMe() const {
  std::string str = "self.";
  for (std::string mod : *_path){
      str += mod + ".read().unwrap().";
  }
  str += "r#"+name;
  return str;
}

string ConstantAccess::PrintMe() const {
  std::string str;
  str += *this->_path + "::"+*this->_path+"::r#"+this->name;
  return str;
}


std::string BinaryRustExpression::PrintMe() const {
  // The exponentiation is a bit special.
  if (type == exponentiation) {
    return "(" + this->castToType(left_expr) + " ).pow(  "+"("+right_expr->PrintMe()+") as u32 )";
  } else if (type == tabularPosition) {
    // We suppose that the left expression is either and a `Variable` (`Id` in the B code), or a `BinaryRustExpression` which is of type `tabularPosition`. We should however be sure it is the case. But if it is, this translation should work.
    auto left = left_expr->PrintMe();
    if (left[0] == '*')
      left = left.substr(1);
    auto right = dynamic_cast<const ArrayAccess*>(right_expr);
    if (right){
       return left + right->PrintMe();
    } else {
      return left+"[("+right_expr->PrintMe()+") as usize]";
    }

  } else {
      std::map<binaryExpression, std::string> assoc = {
        {addition, ") + ("},
        {substraction, ") - ("},
        {multiplication, ") * ("},
        {division, ") / ("},
        {bitwise_or, ") | ("},
        {bitwise_and, ") & ("},
        {bitwise_xor, ") ^ ("},
        {modulo, ") % ("},
        {parameterPosition, ", "},
      };
      if (assoc.find(type)!=assoc.end()){
        return "((" + this->castToType(left_expr) +assoc.at(type)+this->castToType(right_expr) +"))";
      }

      std::map<binaryExpression, std::string> assoc2 = {
        {left_shift, ") << ("},
        {right_shift, ") >> ("},
      };

      if (assoc2.find(type)!=assoc2.end()){
         return " (("+this->castToType(left_expr) + assoc2.at(type)+right_expr->PrintMe()+" as usize))";
      }
  }
  return "//TODO";
}

std::string BinaryRustExpression::PrintMeConst() const {
  // The exponentiation is a bit special.
  if (type == exponentiation) {
    return "("+left_expr->PrintMeConst()+ this->asConversion() + " ).pow(("+right_expr->PrintMeConst()+") as u32 )";
  } else if (type == tabularPosition) {
    // We suppose that the left expression is either and a `Variable` (`Id` in the B code), or a `BinaryRustExpression` which is of type `tabularPosition`. We should however be sure it is the case. But if it is, this translation should work.
    auto left = left_expr->PrintMeConst();
    if (left[0] == '*')
      left = left.substr(1);
    auto right = dynamic_cast<const ArrayAccess*>(right_expr);
    if (right){
       return left + right->PrintMeConst();
    } else {
      return left+"[("+right_expr->PrintMeConst()+") as usize]";
    }

  } else {
      std::map<binaryExpression, std::string> assoc = {
        {addition, ") + ("},
        {substraction, ") - ("},
        {multiplication, ") * ("},
        {division, ") / ("},
        {bitwise_or, ") | ("},
        {bitwise_and, ") & ("},
        {bitwise_xor, ") ^ ("},
        {modulo, ") % ("},
        {parameterPosition, ", "},
      };
      if (assoc.find(type)!=assoc.end()){
        return "(( "+left_expr->PrintMeConst() +this->asConversion() +assoc.at(type)+right_expr->PrintMeConst()+this->asConversion() +"))";
      }

      std::map<binaryExpression, std::string> assoc2 = {
        {left_shift, ") << ("},
        {right_shift, ") >> ("},
      };

      if (assoc2.find(type)!=assoc2.end()){
         return " (("+left_expr->PrintMeConst()+this->asConversion() + assoc2.at(type)+right_expr->PrintMeConst()+" as usize))";
      }
  }
  return "//TODO";
}



std::string RustBinaryPredicate::PrintMe() const {
  // Adding the Rust comparison symbol.
  static const std::map<comparisonSymbol, std::string> assoc = {
    {comparisonSymbol::LessThan, "<"},
    {comparisonSymbol::LessThanOrEqualTo, "<="},
    {comparisonSymbol::EqualTo, "=="},
    {comparisonSymbol::MoreThanOrEqualTo, ">="},
    {comparisonSymbol::MoreThan, ">"},
    {comparisonSymbol::NotEqualTo, "!="},
  };

  return left_expr->PrintMe()+" "+assoc.at(symbol)+" "+right_expr->PrintMe();
}


std::string RustPredicateAggregate::PrintMe() const {
  std::string string;
  static const std::map<comparisonSymbol, std::string> assoc = {
    {comparisonSymbol::And, "&&"},
    {comparisonSymbol::Or, "||"},
  };
  std::string the_symbol = assoc.at(symbol);

  std::vector<const RustPredicate*>::const_iterator it = predicates->begin();
  string += "("+(*it)->PrintMe();

  for (++it; it != predicates->end(); ++it) {
    string += ") "+the_symbol+" ("+(*it)->PrintMe();
  }

  return string+")";
}


std::string RustUnaryPredicate::PrintMe() const {
  // We suppose it is a NOT every time.
  return "!("+predicate->PrintMe()+")";
}


std::string Block::PrintMe() const {
  return "{\n"+_PrintMe(instructions)+"}\n";
}

std::string Block::PrintMeInit() const {
  std::string str;
  for (const RustInstruction* inst : *instructions){
    if (dynamic_cast<const RustAssignement*>(inst)){
      auto inst2 = dynamic_cast<const RustAssignement*>(inst);
      str +=  inst2->PrintMeInit2() + "\n";
    }
  }
  return str;
}



std::string _PrintMe(std::vector<const RustInstruction*>* instructions){
  std::string str;
  for (const RustInstruction* instruction : *instructions) {
    str += instruction->PrintMe();
  }
  return str;
}




std::string Declaration::PrintMe() const {
  std::string str;
  // Mutable by default, even if this makes warnings
  auto arrayType = dynamic_cast<const RustTabular*>(type);
  auto stringType = dynamic_cast<const string_t*>(type);
  if(expr){
    if(arrayType || stringType){
      str = "let mut r#" + *name  +" = " + expr->PrintMe() +";\n";
    } else if (type){
     str =  "let mut r#" + *name  +" = " + expr->PrintMe() + " as " + type->PrintMe()+";\n";
    } else {
      str =  "let mut r#" + *name  +" = " + expr->PrintMe() +";\n";
    }
  } else {
    if(arrayType||stringType){
     str =  "let mut r#" + *name + ": " + type->PrintMe() + ";\n";
    } else if (type){
      str =  "let mut r#" + *name + ": " + type->PrintMe() + " = Default::default();\n";
    } else {
      str = "//let mut r#" + *name + " = TODO ;\n";
    }
  }
  return str;
}

std::string Declaration::PrintMeInit() const {
  std::string str = ((type)? "" : "//");
  str += "pub const ";
  if (type){
    str += "r#"+*this->name + " : " + this->type->PrintMe() + " = " + this->expr->PrintMeConst() + ";\n";
  } else {
    str += "r#"+*this->name + " : " + "TODO" + " = " + this->expr->PrintMeConst() + ";\n";
  }

  return str;
}

std::string FunctionCall::PrintMe() const {
  std::string str;
  // First, if there is several output parameters, we need to initialize them.
 // for (auto op: outputParameters) {
 //   str += op->PrintMe() + " = Default::default();\n";
  //}

  // If the function belongs to another machine, it may need write rights. Therefore, we
  // need to evaluate the call in a block to prevent blocking any other writing in the current block
  if (moduleName != "")
      str += "{ let tmp = ";

  // There’s always a field associated with the converted instance name inside the struct, so, we use `self.`.
  str += "self." + ((moduleName!="")? moduleName + ".write().unwrap()." : "")+ function->name + "(";

  // We add the input parameters. They are given as immutable references. Hopefully, Rust accepts borrows of litterals, so, we can just print "&" and print the expression.
  for (auto ip : inputParameters) {
    str += "&" + ip->PrintMe() + ", ";
  }

  // The output parameters are also `RustExpression`s, but are only `Variable`s. They are translated as mutable borrows.
  for (auto op: outputParameters) {
    str += "&mut " + op->PrintMe() + ", ";
  }

  str += ");\n";

  if (moduleName != "")
      str += "tmp }";

  return str;
}


std::string DelegateCall::PrintMe() const {
  std::string str;
  // There’s always a field associated with the converted instance name inside the struct, so, we use `self.`.
  str += "{ let tmp = self." + moduleName + ".write().unwrap()." + functionName + "(";

  //parameters are already a reference, no need to add &
  for (auto ip : inputParameters) {
    str += "r#"+*ip + ", ";
  }

  // parameters are already a reference, no need to add &
  for (auto op: outputParameters) {
    str +=  "r#"+*op + ", ";
  }

  str += "); tmp }\n";
  return str;
}


std::string RustArray::PrintMe() const {
  std::string str;

  str += "[";
  for (const RustExpression* re : values) {
    str += re->PrintMe() + ", ";
  }

  // Removing the two latter chars is useless (`rustfmt` can remove them).

  str += "]";

  return str;
}


std::string RustWhile::PrintMe() const {
  std::string str;

  str += "while ";
  str += condition->PrintMe();
  str += " {\n";
  for (const RustInstruction* ri : instructions) {
    str += ri->PrintMe();
  }
  str += "}\n";

  return str;
}


std::string enumType::PrintMe() const {
  std::string str;

  str += *name;

  return str;
}

std::string enumType::PrintMeDefault() const {
  std::string str;

  str += *name + "::default()";

  return str;
}


std::string Enumerator::PrintMe() const {
  std::string str;

  str += _enum;
  str += "::";
  str += name;

  return str;
}


std::string RustCase::PrintMe() const {
  std::string str;

  std::string vals;
  for (std::size_t  i = 0; i < value->size() -1  ; i++) {
        vals += value -> at(i) -> PrintMe() + " | ";
   //str.back() = ',';  // Modifier le dernier caractère de la chaîne
    }
  vals += value -> back() -> PrintMe() ;
  str += vals + " => " + then -> PrintMe();
  return str;
}


std::string Match::PrintMe() const {


    std::string str;
    str += str + "match " + target -> PrintMe() + "{\n";
    for (std::size_t  i = 0; i < cases->size() ; i++) {
        str += cases -> at(i) -> PrintMe();
   //str.back() = ',';  // Modifier le dernier caractère de la chaîne
    }

  str += "_ => " + _default ->PrintMe();

  str += "}";
    return str;

}


std::string RustUniformArray::PrintMe() const {
  std::string str;
  str += "["+value->PrintMe()  + "; (" + size->PrintMe() + " + 1) as usize" +"]";
  return str;
}

std::string RustExpression::PrintMeDefault() const {
  return "Default::default()";
}

std::string RustExpression::castToType(const RustExpression* target) const {
  return  this->getType()->PrintMe() +"::try_from(" + target->PrintMe() + ").unwrap()" ;
}

std::string BinaryRustExpression::castToType(const RustExpression* target) const {
  if(resultType){
    return this->getType()->PrintMe() +"::try_from(" + target->PrintMe() + ").unwrap()" ;
  } else {
    return target->PrintMe();
  }
}

std::string RustArray::castToType(const RustExpression* target) const {
  return target->PrintMe();
}

std::string RustUniformArray::castToType(const RustExpression* target) const {
  return target->PrintMe();
}

std::string ArrayAccess::PrintMe() const {
  std::string str = array->PrintMe();
  if (str[0] == '*')
      str = str.substr(1);
  for (auto index : indexes){
    str += "["+ index->PrintMe() +" as usize]";
  }
  return str;
}


std::string IntegerType::PrintMe() const {
  return "integer_t";
}

std::string ErrorType::PrintMe() const {
  return "error_t";
}

std::string IntegerType::PrintMeDefault() const {
  return "integer_t";
}

std::string ErrorType::PrintMeDefault() const {
  return "error_t";
}


std::string RustExpression::asConversion() const {
  return " as " + this->getType()->PrintMe() ;
}

std::string BinaryRustExpression::asConversion() const {
  if(resultType){
    return " as " + resultType->PrintMe();
  } else {
    return "";
  }
}

std::string RustArray::asConversion() const {
  return "";
}

std::string RustUniformArray::asConversion() const {
  return "";
}

std::string RustExpression::PrintMeConst() const {
  return this->PrintMe();
}
