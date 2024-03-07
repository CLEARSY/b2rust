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
#ifndef H_PARSER
#define H_PARSER

#include <tinyxml2.h>
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <map>
#include <string>
#include <functional>
#include <set>
#include <variant>
#include <optional>
#include <unordered_set>

#include "recognized_types.h"
#include "../input.h"
#include "../checker/checker.h"
#include "./bxml/binarypredop.h"


using namespace tinyxml2;

#include <any>


using cpp_int = boost::multiprecision::cpp_int;


template <typename T>
using simpleAction = std::pair<T*, T (*) (XMLElement*)>;
template <typename T>
using vectorAction = std::pair<std::vector<T>*, T (*) (XMLElement*)>;

template<typename... Ts>
using elementAction = std::optional<std::variant<simpleAction<Ts>..., vectorAction<Ts>...>>;

using attributeActions = const std::map<
  std::string,
  std::variant<
    const std::string**,
    const cpp_int**,
    const unsigned**,
    const bool**,
    const binaryPredOp**
    >>;



/*
  Contains parsing functions (so that they are ordered...)
  Also contains a translated shape of a module.
 */

class Machine;

class Parser {
public:
  // Translated shape of a module.
  const Machine* am;
  const std::vector<Machine*>* ref;
  const Machine* impl;

  bool is_base(){
    return impl == NULL;
  }
 
  // --- FIELDS CONTAINING INFORMATION filled by the Checker so that they can be transmitted to the translater. So, just after the parsing, they have to be empty.
  // The children `Parser`s.
  std::unordered_set<Parser*> children;
  
  // Concerning the enums.
  // These two first maps are maps which will be transmitted to parents.
  // An association between a set name and the module it is defined in.
  std::unordered_map<std::string, const std::string*> transmittedSetList;
  // A list of associations between enumerators and the enum they’re in.
  // A list of pairs (enumerator, set it is in), for example (red, color).
  std::unordered_map<std::string, const std::string*> transmittedEnumeratorsSet;

  // Same as `transmittedSetList`, but also contains private sets (those defined in the implementation).
  std::unordered_map<std::string, const std::string*> privateSetList;
  // Same as `transmittedEnumeratorsModule`, but also contains private sets (those defined in the implementation).
  std::unordered_map<std::string, const std::string*> privateEnumeratorsSet;

  
  // The types of the concrete variables and concrete constants. CAUTION: this `map` is broken if accessed in another component !!!
  std::unordered_map<std::string, const RustType*> variableTypes;
  std::unordered_map<std::string, const RustType*> constantTypes;
    
  
  // END OF FIELDS CONTAINING INFORMATION, etc. (cf supra)

public:


  // Just searches them in the implementation.
  const std::unordered_set<const std::string*>* getConcreteConstants() const;

  // Searches them everywhere.
  const std::unordered_set<const std::string*>* getConcreteVariables() const;

  //search in abstract machine  
  const std::unordered_set<const std::string*>* getParametersDeclaration() const;
  
  // The checkme function.
  void checkMe();

  // Can be reimplemented in child classes.
  virtual void checkMe(machineType, std::unordered_map<std::string, const std::string*>*) const;

  // Prints the object.
  virtual std::string* debugMe() const;
  
  Parser();
  Parser(const Module*);

protected:
  static bool checking_error;

public:

  // --- FONCTIONS WORKING ON NODES


  
  // If some elements are present in the list, an action is executed. However only 1 element of each type is expected, and they have to be in specified order.
  // Expects an element and a list of triplets which consist of:
  // 1. `s1`, A string (element name).
  // 2. `t& o`, an object reference of type `t`.
  // 3. A `void` function, `f`, which takes as argument an object reference of type `t` and an element pointer.
  // All the elements name are expected to be present **at most once** among the names of the subelements of the element.
  // All the children of the element have to be elements with a name.
  // Useless note: if these conditions are not respected, something **bad** shall happen without any warning (likely a segmentation fault).
  // Used, for example, in `Actions`.
  template <typename T> static void NodeActionForEachPresent(XMLElement* const, const std::vector<std::tuple<
							     std::string,
							     T,
							     void (*) (XMLElement*, T)>>);
  
  // An action is executed on every children of the element. Each action shall modify the given set/map/vector, likely by adding an element.
  // All the children have to be elements: no texts, comments, etc.
  // Used in `Concrete Variables`, in `Nary_Pred`...
  template <typename T> static void NodeActionForEach(XMLElement*, T, void (*) (XMLElement*, T));

  // Interface of `NodeActionForEach`. Exactly the same, except the children shall provide an object depending on their name. So, the user has to provide a map of functions to used associated to the name.
  // EDIT: likely not a good idea.
  // template <typename T> static void NodeActionForEachDifferent(XMLElement*, T, const std::map<std::string, void (*) (XMLElement*, T)>);



  // Expects an element with exactly one child. Execute an action on this child which shall likely modify an object we give a reference to.
  template <typename T> static void NodeAction(XMLElement*, T, void (*) (XMLElement*, T));

  // Expects an element with exactly two children. Execute an action on this children which shall likely modify an object, associated to them, and we give a reference to.
  template <typename T, typename U> static void NodeTwoActions(XMLElement*, T, U, void (*) (XMLElement*, T), void (*) (XMLElement*, U));
  
 
  // Re-new parsing & a bit of checking functions.

  // New parsing & checking function. Give it an element, a map which associates with every string (i.e. an attribute) a string pointer.
// For each attribute, if it is found in the map, the string pointed is modified.
// If the name is not found, then it means that this attribute is not recognized. A fail occurs with the specified error message, if it is not null.
// Note that if a string is expected (i.e. if present in the map) but not searched (it is not in the element’s attribute), nothing happens.
  static void workOnAttributes(XMLElement* const, attributeActions*, const std::string);

  
  //
  template<typename... Ts>
  static void workOnElements(XMLElement*, std::map<std::string, elementAction<Ts...>>, const std::string);


  static const std::string* GetText(XMLElement*);


  // Classic error message.
  static std::string uncompliant;
  static std::string nonTranslatableYet;
};


// Template implementations.
#include "parser.tcc"

#endif
