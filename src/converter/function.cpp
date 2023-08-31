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
#include "function.h"
#include "../b2rust.h"
#include "../debug.h"
#include "../parser/bxml/assertion.h"
#include "../parser/bxml/id.h"
#include "../parser/bxml/varin.h"
#include "./declaration.h"
#include "./delegatecall.h"
#include "./functioncall.h"

//================== Create a function with public declaration==================//
const Function* Operation::ConvertMe(const Context* old_context) const {
  // We clone the context.
  Context* context = new Context(*old_context);

  // We add to the context the list of input/output parameters.
  return new Function(context, this, false);
}

//================== Create a function with private declaration==================//
const Function* Operation::ConvertMePrivate(const Context* old_context) const {
  // We clone the context.
  Context* context = new Context(*old_context);

  // We add to the context the list of input/output parameters.
  return new Function(context, this, true);
}

Function::Function(Context* context, const Operation* const operation, const bool prive_arg)
    : name(*operation->name),
      prive(prive_arg) {

  if (operation->inputParameters) {
    for (const Id* id : operation->inputParameters->id) {
      context->parameters.insert({*id->value, operation->types->at(*id->value)});
      inputParameters.push_back({*id->value, (operation->types->at(*id->value))->convertIfPartial(context)});
    }
  }
  if (operation->outputParameters) {
    for (const Id* id : operation->outputParameters->id) {
      context->parameters.insert({*id->value, operation->types->at(*id->value)});
      outputParameters.push_back({*id->value, (operation->types->at(*id->value))->convertIfPartial(context)});
    }
  }

  operation->body->sub->ConvertMe(context, &instructions);
}

//=======================================END==================================================//

//=============Create a function whose body is a function call to the module's function who has the real implementation======//
const Function* Operation::ConvertMePromoted(const Context* old_context, const std::string* module) const {
  // We clone the context.
  Context* context = new Context(*old_context);

  // We add to the context the list of input/output parameters.
  return new Function(context, module, this);
}

Function::Function(Context* context, const std::string* module, const Operation* const operation)
    : name(*operation->name),
      prive(false) {

  auto delegation = new DelegateCall(module, operation->name);

  if (operation->inputParameters) {
    for (const Id* id : operation->inputParameters->id) {
      context->parameters.insert({*id->value, operation->types->at(*id->value)});
      inputParameters.push_back({*id->value, operation->types->at(*id->value)->convertIfPartial(context)});
      delegation->inputParameters.push_back(id->value);
    }
  }
  if (operation->outputParameters) {
    for (const Id* id : operation->outputParameters->id) {
      context->parameters.insert({*id->value, operation->types->at(*id->value)});
      outputParameters.push_back({*id->value, operation->types->at(*id->value)->convertIfPartial(context)});
      delegation->outputParameters.push_back(id->value);
    }
  }

  instructions.push_back(delegation);
}

//=======================================END=======================================================================//

//=================== Create a function with no function body, usefull for basic module=========================//
const Function* Operation::ConvertMeNoBody(const Context* old_context) const {
  // We clone the context.
  Context* context = new Context(*old_context);

  // We add to the context the list of input/output parameters.
  return new Function(context, this, 1);
}

Function::Function(Context* context, const Operation* const operation, const int)
    : name(*operation->name),
      prive(false) {

  if (operation->inputParameters) {
    for (const Id* id : operation->inputParameters->id) {

      context->parameters.insert({*id->value, operation->types->at(*id->value)});
      inputParameters.push_back({*id->value, operation->types->at(*id->value)->convertIfPartial(context)});
    }
  }
  if (operation->outputParameters) {
    for (const Id* id : operation->outputParameters->id) {
      context->parameters.insert({*id->value, operation->types->at(*id->value)});
      outputParameters.push_back({*id->value, operation->types->at(*id->value)->convertIfPartial(context)});
    }
  }
}
//=======================================END========================================================//

void NarySub::ConvertMe(const Context* context, std::vector<const RustInstruction*>* instructions_arg) const {
  for (Instruction* instruction : instructions) {
    instruction->ConvertMe(context, instructions_arg);
  }
}

void Assertion::ConvertMe(const Context* context, std::vector<const RustInstruction*>* instructions) const { body->ConvertMe(context, instructions); }

void VarIn::ConvertMe(const Context* context, std::vector<const RustInstruction*>* instructions) const {
  /* The checker ensures the local variables are well-defined in the body.
     So, there’s nothing special to do except translate blindly the instructions (the `BecomesIn` will be translated as `let`..., so, declarations),
     and will be into a block. */
  auto subinstructions = new std::vector<const RustInstruction*>;

  // The context has to be duplicated; the field `local` will contain the local variables types. (Some might already be inside...)
  Context newContext = *context;
  std::unordered_map<std::string, const RustType*> copy = types;

  newContext.local.merge(copy);

  body->ConvertMe(&newContext, subinstructions);

  Block* block = new Block(subinstructions);
  instructions->push_back(block);
}
