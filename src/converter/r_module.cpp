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
#include "r_module.h"
#include "../b2rust.h"
#include "../debug.h"
#include "../parser/miscellaneous.h"
#include "function.h"
#include "../util/tools.h"
#include <vector>

auto customEqual = [](const std::string* ptr1, const std::string* ptr2) { return *ptr1 == *ptr2; };

RustModule::RustModule(const Parser* const module)
    : parser(module),
      am(module->am),
      ref((module->ref->size()) ? module->ref : NULL),
      impl((module->impl) ? module->impl : NULL),
      context(),
      name(*module->am->name) {
  // ------ FIELDS INITIALISATION ----
  // We will call some prototypes... Just to make it easier to read.

  if (!is_base()) {
    // --- Add the `mod`s. Well, it is only suitable for the main module. On other modules, it has to remain empty.
    if (name == Input::main_module_name) {
      // We are dealing with the main module (= the entry module).
      // Are there imports in the project? We have to add a "mod" for every import recursively found.
      for (const auto& [key, value] : b2rust::p_imports) {
        mods.insert(&key);
      }
    } else {
      // --- Add the `uses`. Well, it is only suitable for non-main modules.
      // We have to add an "use" for every import of the component.
      if (impl->imports) {
        // Créer un unordered_set temporaire pour suivre les valeurs uniques
        std::unordered_set<std::string> uniqueValues;
        for (const ReferencedMachine* rm : impl->imports->referencedMachine) {
          const std::string* const name = rm->name;
          // Vérifier si la valeur pointée n'a pas déjà été rencontrée
          if (uniqueValues.find(*name) == uniqueValues.end()) {
            // Valeur non rencontrée, nous l'ajoutons aux valeurs uniques et à uses
            uniqueValues.insert(*name);
            uses.insert(name);
          }
        }
      }
    }
  }

  // In all cases, enums have to be added for each imported enum even thourght it is not used
  for (auto const& [key, value] : module->transmittedSetList) {
    // std::cout << "We find: " << key << ", " << *value << std::endl;
    // Not every set shall have an `use` associated. Only the ones of imported modules. (We do not go over each child because of possible
    // collisions...?)
    if (*value != *module->am->name) {
      // Ok, we can add this one.
      // `b2rust` structure is not well respected here... It might be worth it to change this.
      // If it is the entry module, we exceptionnaly use `pub use`s.
      if (name == Input::main_module_name) {
        pubUses.insert(new std::string(*value + "::" + key));
      } else {
        uses.insert(new std::string(*value + "::" + key));
      }
    }
  }

  // --- `instances` initialisation. Just needs to be called after the `uses` initialisation. It adds name associations to the context.
  // /!\ CREATEINSTANCES HAS ALSO THE ROLE TO RECURSIVELY TRANSLATE THE IMPORTED COMPONENTS, and feed the "children" field.
  CreateInstances(&context);
  // Concerning the global variables, it is easy.
  context.globalVariables = parser->variableTypes;
  context.globalConstants = parser->constantTypes;
  context.enumeratorsSet = &parser->privateEnumeratorsSet;

  // From now, the context cannot be changed (usage is to clone it).

  // --- Translating the `enum`s. It can be done anywhere, but let’s do it there...
  TranslateEnumsFrom(am);

  if (ref){
    for (auto refinement : *ref){
      TranslateEnumsFrom(refinement);
    }
  }


  if (impl) {
    TranslateEnumsFrom(impl);
  }

  auto path = new std::vector<std::pair<std::string, std::string>>();
  FindDataAssociation(&context, path);
 
  FindConstantAssociation(&context);

  for (const std::string* s : *parser->getParametersDeclaration()) {
    parameters.insert(
        {*s, (parser->variableTypes.find(*s) != parser->variableTypes.end()) ? parser->variableTypes.at(*s)->convertIfPartial(&context) : NULL});
  }

  for (const std::string* s : *parser->getConcreteConstants()) {
    constants.insert(
        {*s, (parser->constantTypes.find(*s) != parser->constantTypes.end()) ? parser->constantTypes.at(*s)->convertIfPartial(&context) : NULL});
  }
  for (const std::string* id : *parser->getConcreteVariables()) {
    variables.insert(
        {*id, (parser->variableTypes.find(*id) != parser->variableTypes.end()) ? parser->variableTypes.at(*id)->convertIfPartial(&context) : NULL});
  }

  // Caution: needs to be called after `CreateVariables`!!
  // NOTE: it also add the `VALUES`-clause values. (Object `values`.)
  CreateInitialisations(&context);

  // not sure about the position
  CreateInstancesArguments(&context);


  CreateFunctions(&context);
}

void RustModule::TranslateEnumsFrom(const Machine* machine) {
  if (machine->sets) {
    for (const Set* set : machine->sets->set) {
      std::pair<std::string, std::vector<std::string>> new_enum;
      new_enum.first = *set->id->value;
      if (set->enumeratedValues) {
        for (const Id* id : set->enumeratedValues->id) {
          new_enum.second.push_back(*id->value);
        }
      }
      enums.push_back(new_enum);
    }
  }
}

void RustModule::CreateInstances(Context* context) {
  if (!is_base()) {
    if (impl->imports) {
      // The renaming prefix. Useful to prevent collision and to give an idea of the order of initialization.
      unsigned int prefix = 1;
      // There are at least one import to add a instance for.
      for (const ReferencedMachine* rm : impl->imports->referencedMachine) {
        const std::string* rm_name = rm->name;
        const std::string* rm_instance = rm->instance;
        std::string* renamed_name = new std::string("_" + std::to_string(prefix) + "_");
        // We use the instance name if provided, the machine name otherwise.
        if (rm_instance) {
          // A rename is provided.
          *renamed_name += *rm_instance;
          // We add the association (instance name -> renamed name) to the context.
          context->instancesNameAssoc.insert({*rm_instance, renamed_name});
        } else {
          *renamed_name += *rm_name;
          // If an operation from this module is called, there won’t be any instance given. So, we need to put into the context all the possible
          // associations (function name -> renamed instance). The implementation necessary exists, BUT doesn’t have necessarily operations!
          Parser* p_import = b2rust::p_imports.at(*rm_name);
          // const Machine* implementation_we_want_the_functions_from = (p_import->impl) ? p_import->impl : p_import->am;
          const Machine* implementation_we_want_the_functions_from = p_import->am;
          if (implementation_we_want_the_functions_from->operations) {
            for (const Operation* op : implementation_we_want_the_functions_from->operations->operations) {
              context->operationNameAssoc.insert({*op->name, renamed_name});
            }
          }
          context->machineNameAssoc.insert({*rm_name, renamed_name});
        }

        context->referencedMachineNames.insert(rm_name);

        // context->machineNameAssoc.insert({*rm_name, renamed_name});

        // In either case, we add the instance.
        instances.push_back({renamed_name, rm_name});
        // We also add the instance name to the `instances_init` object...
        instances_init.push_back(renamed_name);

        prefix++;

        // We take the occasion to translate this mere imported machine... If it has not already be done, of course.
        // std::cout << *name << std::endl;
        auto child = b2rust::r_imports.find(*rm_name);
        if (child == b2rust::r_imports.end()) {
          // The conversion has not already be done here. Let’s do it.
          // std::cout << *name << std::endl;
          RustModule* newChild = new RustModule(b2rust::p_imports.at(*rm_name));
          b2rust::r_imports.insert({*rm_name, newChild});

          // We add it to the list of children.
          children.push_back(newChild);
        } else {
          // We add it to the list of children.
          children.push_back(child->second);
        }
      }
    }
  }
}

void RustModule::CreateInstancesArguments(Context* context) {
  int i = 0;
  if (impl && impl->imports)
    for (const ReferencedMachine* rm : impl->imports->referencedMachine) {

      if (rm->parameters) {
        std::vector<const RustExpression*> args;
        std::transform(rm->parameters->expr.begin(), rm->parameters->expr.end(), std::back_inserter(args),
                       [context](const Exp* exp) { return exp->ConvertMe(context); });
        instancesArguments.insert({instances_init.at(i), args});
      }
      i++;
    }
}

void RustModule::FindDataAssociation(Context* context2, std::vector<std::pair<std::string, std::string>>* path) {
  if (impl && impl->imports) {
    for (const ReferencedMachine* rm : impl->imports->referencedMachine) {
      const std::string* rm_name = rm->name;
      auto path2 = new std::vector<std::pair<std::string, std::string>>(*path);
      path2->push_back(
          std::make_pair(rm->instance ? *context.instancesNameAssoc.at(*rm->instance) : *context.machineNameAssoc.at(*rm_name), *rm_name));

      auto r_child = b2rust::r_imports.at(*rm_name);
      auto cvs = r_child->parser->getConcreteVariables();
      for (auto cv : *cvs) {

        if (rm->instance) {
          context2->variableNameAssoc.insert({(*rm->instance + "." + *cv), path2});
        } else {
          context2->variableNameAssoc.insert({*cv, path2});
        }
      };

      r_child->FindDataAssociation(context2, path2);
    }
  }
}

void RustModule::FindConstantAssociation(Context* context2) {
  if (impl && impl->imports) {
    for (const ReferencedMachine* rm : impl->imports->referencedMachine) {
      const std::string* rm_name = rm->name;
      auto r_child = b2rust::r_imports.at(*rm_name);
      auto ccs = r_child->parser->getConcreteConstants();

      for (auto cc : *ccs) {
        context2->constantNameAssoc.insert({*cc, rm_name});
      };

      r_child->FindConstantAssociation(context2);
    }
  }
}

void RustModule::CreateFunctions(const Context* context) {
  // The `main` is added manually and isn’t part of the `vector`.
  // There might be no operations. But if there’s one or more, we need to add them.
  const Machine* target = (is_base()) ? am : impl;

  AddLocalOperations(context, target);
  CreatePromotedOperations(context);
  CreateExtendedOperations(context);
  CreateOperations(context, target);
}

void RustModule::AddLocalOperations(const Context* context, const Machine* target) {
  if (target->localOperations) {
    for (auto operation : target->localOperations->operations) {
      auto fun = operation->ConvertMeNoBody(context);
      context->localFunctions->insert({fun->name, fun});
    }
  }
}

void RustModule::CreatePromotedOperations(const Context* context) {
  if (impl && impl->imports && impl->promotes) {
    for (const ReferencedMachine* rm : impl->imports->referencedMachine) {
      auto rm_name = rm->name;
      // the main may contains the promoted operation of other imports, need to check it later
      //  maybe the concern do not exist because mutual imports are not allowed
      Parser* p_import = b2rust::p_imports.at(*rm_name);

      // assuming the import is not a base module
      auto mch = (p_import->impl) ? p_import->impl : p_import->am;
      auto vec_promoted = impl->promotes->promotedOperationType;
      // at least one otherwise atelier b would not be happy because of promotes clause

      // si les operations cherché dans le import est aussi dans la clause promotedoperation alors on ajoute dans la fonction
      if (mch->operations)
        for (const Operation* const operation : mch->operations->operations) {
          for (auto ptr : vec_promoted) {
            if (Tools::getLastWord(ptr->name) == *operation->name) {
              std::string newName = Tools::getLastWord(ptr->name);
              // si le module n'a pas été renommé
              if (newName.size() == (ptr->name).size()) {
                functions.push_back(operation->ConvertMePromoted(context, context->operationNameAssoc.at(*operation->name)));
              } else {
                functions.push_back(operation->ConvertMePromoted(context, context->instancesNameAssoc.at(Tools::getFirstWord(ptr->name))));
              }
            }
          };
        }
    }
  }
}
void RustModule::CreateExtendedOperations(const Context* context) {
  if (impl && impl->extends) {
    for (const ReferencedMachine* rm : impl->extends->referencedMachine) {
      auto rm_name = rm->name;
      Parser* p_import = b2rust::p_imports.at(*rm_name);
      auto mch = p_import->am;
      if (mch->operations)
        for (const Operation* const operation : mch->operations->operations) {
          if (rm->instance) {
            functions.push_back(operation->ConvertMePromoted(context, context->instancesNameAssoc.at(*rm->instance)));
          } else {
            functions.push_back(operation->ConvertMePromoted(context, context->machineNameAssoc.at(*mch->name)));
          }
        }
    }
  }
}

void RustModule::CreateOperations(const Context* context, const Machine* target) {
  if (target->operations) {
    for (const Operation* const operation : target->operations->operations) {
      // is it declared in localop ? if this is the case it should be declared as private
      if (target->localOperations) {
        auto l_operations = target->localOperations->operations;
        auto it = std::find_if(l_operations.begin(), l_operations.end(), [&](Operation* op) { return *op->name == *operation->name; });
        if (it != l_operations.end()) {
          functions.push_back(operation->ConvertMePrivate(context));
        } else {
          functions.push_back(operation->ConvertMe(context));
        }
      } else {
        if (impl) {
          functions.push_back(operation->ConvertMe(context));
        } else {
          functions.push_back(operation->ConvertMeNoBody(context));
        }
      }
    }
  }
}





void RustModule::CreateInitialisations(const Context* context) {
  // Add value initialisation for constants.
  // The expression could contain an `Id`, beware of the context.
  const Machine* target = (is_base()) ? am : impl;
  if (target->values) {
    for (const Valuation* valuation : target->values->valuation) {
      auto var = _Variable(context, valuation->ident);
      values.push_back(new Declaration(&var->name, valuation->exp->ConvertMe(context), var->getType()));
    }
  }
  // Add instructions contained in the initialisation.
  Sub* initialisation = target->initialisation->sub;
  if (initialisation) {
    initialisation->ConvertMe(context, &initialisations);
  }
}