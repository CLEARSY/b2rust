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
#include "functioncall.h"
#include "../debug.h"
#include "../parser/bxml/id.h"
#include "../parser/bxml/operationcall.h"
#include "declaration.h"
#include "miscellaneous.h"

// The constructor for "easy" fields.
FunctionCall::FunctionCall(const std::string* moduleName_arg, const Function* _function)
    : function(_function) {
  if (moduleName_arg) {
    moduleName = *moduleName_arg;
  } else {
    moduleName = "";
  }
}

//================================FunctionCall====================================//
void OperationCall::ConvertMe(const Context* context, std::vector<const RustInstruction*>* instructions) const {

  Context newContext = *context;

  const std::string* renamed = name->id->instance;

  auto functionName = renamed ? name->id->component : name->id->value;

  const std::string* moduleName_arg;

  // If the instance is given, we have an idea of the actual name of the module the function is in, and we just need to find the corrected
  // instance name using the context. If it is not given, we have to guess it using the useful `operationNameAssoc` field of the context.
  // Anyhow, we suppose every field is well-defined in the associated map.
  if (renamed) {
    moduleName_arg = context->instancesNameAssoc.at(*renamed);
  } else if (context->operationNameAssoc.count(*name->id->value)) {
    moduleName_arg = context->operationNameAssoc.at(*name->id->value);
  } else {
    moduleName_arg = NULL; // local op
  }

  auto isRightName = [functionName](const Function* function) { return function->name == *functionName; };

  const Function* func = NULL;


  //===========Find the func that would be call==================//

  // is the called funciton defined outside of the module ? 
  if (moduleName_arg != NULL) {
    for (const auto& rm_name : context->referencedMachineNames) {
      auto funcs = b2rust::r_imports.at(*rm_name)->functions;
      auto it = std::find_if(funcs.begin(), funcs.end(), isRightName);
      if (it != funcs.end()) {
        func = *it;
      }
    }
  } else {
    // otherwise, it must be a local functions 
    func = context->localFunctions->at(*functionName);
  }

  //==========================================================//


  auto subinstructions = new std::vector<const RustInstruction*>;



  //=============Copy input and output parameters type ==============//

  std::vector<const RustType*> inputType;
  std::vector<const RustType*> outputType;
  std::transform(func->inputParameters.begin(), func->inputParameters.end(), std::back_inserter(inputType), [](std::pair<std::string, const RustType *> pairs) { 
    return pairs.second; 
  });
  std::transform(func->outputParameters.begin(), func->outputParameters.end(), std::back_inserter(outputType), [](std::pair<std::string, const RustType *> pairs) { 
    return pairs.second; 
  });


  //==========Copy input parameters============//
  __ExpVector* inputCopies = new __ExpVector;
  if (inputParameters) {
    int cpt = 1;
    for (const Exp* exp : inputParameters->exp) {
      Id* cp = new Id;
      cp->value = new std::string("inputCopy" + std::to_string(cpt));
      inputCopies->exp.push_back(cp);
      auto paraType = inputType.at(cpt-1)->convertIfPartial(context);
      newContext.local.insert({*cp->value, paraType});
      subinstructions->push_back(new Declaration(cp->value, exp->ConvertMe(&newContext),paraType));
      cpt++;
    }
  }

  //===========Copy output parameters================//
  __IdVector* outputCopies = new __IdVector;
  if (outputParameters) {
    int cpt = 1;
    for (const Id* id : outputParameters->id) {
      Id* cp = new Id;
      cp->value = new std::string("outputCopy" + std::to_string(cpt));
      outputCopies->id.push_back(cp);
      auto paraType = outputType.at(cpt-1)->convertIfPartial(context);
      newContext.local.insert({*cp->value, paraType});
      subinstructions->push_back(new Declaration(cp->value, id->ConvertMe(&newContext),paraType));
      cpt++;
    }
  }

  //=================Create the function call==============================//

  FunctionCall* fc = new FunctionCall(
      // The module name.
      moduleName_arg,

      func);

  // Now, we need to parse copies of input and output parameters.
  if (inputCopies) {
    for (const Exp* exp : inputCopies->exp) {
      fc->inputParameters.push_back(exp->ConvertMe(&newContext));
    }
  }

  if (outputCopies) {
    for (const Id* id : outputCopies->id) {
      fc->outputParameters.push_back(id->ConvertMe(&newContext));
    }
  }

  // Now we can add the function call to the instructions.
  subinstructions->push_back(fc);



  //=====================Do not forget to assign the real output parameter by the copy============//
  if (outputParameters) {
    for (size_t i = 0; i < outputParameters->id.size(); i++) {
      auto assignable = outputParameters->id.at(i);
      auto assigner = outputCopies->id.at(i);
      subinstructions->push_back(new RustAssignement(assignable->ConvertMe(&newContext), assigner->ConvertMe(&newContext)));
    }
  }

  delete inputCopies;
  delete outputCopies;
  
  Block* nfc = new Block(subinstructions);
  instructions->push_back(nfc);
}
