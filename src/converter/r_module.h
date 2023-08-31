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
#ifndef H_MODULE
#define H_MODULE

#include <vector>

#include "../parser/bxml/machine.h"
#include "types.h"

class Function;

class RustModule {
  template <typename T> friend std::string* printIt(T*);

public:
  // --- Convenience fields.

  const Parser* const parser;

  const Machine* const am;
  const std::vector<Machine*>* const ref;
  const Machine* const impl;

  // Context
  Context context;

  bool is_base() { return impl == NULL; };

  std::vector<const RustModule*> children;

public:
  // ------- FIELDS WHICH WILL BE TRANSLATED INTO RUST.

  // The `mod`s. Only suitable for the main module.
  std::unordered_set<const std::string*> mods;

  // The `pub use`s. Only suitable for the main module. Used for the sets.
  std::unordered_set<const std::string*> pubUses;

  // The `uses`. Equivalent of the imports. Forbidden for the main module.
  std::unordered_set<const std::string*> uses;

  // The name of the module.
  std::string const name;

  // The enums. Associated to the sets inside a machine and its implementation.
  std::vector<std::pair<std::string, std::vector<std::string>>> enums;

  // --- CONCERNING THE STRUCT ATTRIBUTES
  // The instances of imported modules. Contains exactly the names of `uses`, but preceded with a rename.
  std::vector<std::pair<const std::string*, const std::string*>> instances;

  // Arguments of imported modules.
  std::map<const std::string*, std::vector<const RustExpression*>> instancesArguments;

  // Parameters of current module
  std::map<const std::string, const RustType*> parameters;

  // The list of variables. They shall be listed in the struct.
  std::map<const std::string, const RustType*> variables;

  // The list of constants. They shall be listed in the struct implementation as a static constants.
  std::map<const std::string, const RustType*> constants;

  // --- CONCERNING THE INITIALIZATION
  // We repeat the instances name for their initialization. It is useless (they are already in the `instances` object), but it helps to have a
  // straightforward printing.
  std::vector<const std::string*> instances_init;

  // Initialization instructions for the values of the concrete constants.
  std::vector<const RustInstruction*> values;

  // List of instructions for initialisation.
  std::vector<const RustInstruction*> initialisations;

  // The list of functions.
  vector<const Function*> functions;

  RustModule();
  RustModule(const Parser*);

  void TranslateEnumsFrom(const Machine*);

private:

  // It adds name associations to the context and recursively translate imported module and feed the "children" field.
  void CreateInstances(Context*);


/**
 * @brief Finds and associates variables defined in other modules with the path taken
 * from the current module to the module where the variable is defined.
 *
 * @param context Pointer to the current context.
 * @param pathPairs Pointer to a vector of pairs representing the path taken to reach the module.
 *                  The first element of each pair gives the reformatted module name, and the second
 *                  element gives the original module name.
 */
  void FindDataAssociation(Context*, std::vector<std::pair<std::string, std::string>>*);

  /**
 * @brief Finds and associates constants defined in other modules with the module name
 *
 * @param context Pointer to the current context.
 */
  void FindConstantAssociation(Context*);

/**
 * @brief Convert the module paramaters and fill the field parameters
 * @param context Pointer to the current context.
 */
  void CreateInstancesArguments(Context*);

//==============Functions==========================//
  void CreateFunctions(const Context*);

  //Should be called in the firt instruction of create functions
  void AddLocalOperations(const Context*, const Machine*);
  void CreatePromotedOperations(const Context*);
  void CreateExtendedOperations(const Context*);

  //Three possibilities, create a local function (private), or a public function or a function without function body
  void CreateOperations(const Context*, const Machine*);

//=================END==============================//

  //Translate initialisation clause
  void CreateInitialisations(const Context*);

public:
 
  std::string PrintMe() const;

  friend ostream& operator<<(ostream& os, const RustModule* const);

private:
  std::string* debugMe() const;
};

#endif
