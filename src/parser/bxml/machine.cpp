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
#include "machine.h"
#include "../expression_leaf.h"
#include "./assignementsub.h"
#include "./valuation.h"


const Machine_Values* _Machine_Values(XMLElement* element) {
  auto mv = new Machine_Values;
  
  vectorAction<const Valuation*> a_valuation = {&mv->valuation, &_Valuation};
  Parser::workOnElements<
    const Valuation*
    >(element, {
	{"Attr", nullopt},
	{"Valuation", a_valuation}
      },
      Parser::uncompliant);

  return mv;
}


Machine::Machine(XMLElement* implementation) {
  // Let’s just ignore the attributes for now...
    // let's ignore the attributes except name

 
  attributeActions a_name = {
    {"name", &name},
    {"version", &useless},
    {"type", &useless},
    {"semantic", &useless},
    {"b0check", &useless},
    {"position", &useless},
    {"xmlns", &useless}
  };

  Parser::workOnAttributes(implementation, &a_name, Parser::uncompliant);
  simpleAction<const std::string*> a_abstraction = {&abstraction, &GetText};
  simpleAction<const ParametersDeclaration*> a_parameters = {&parameters, &_ParametersDeclaration};
  simpleAction<const InstanceListType*> a_includes = {&includes, &_InstanceListType};
  simpleAction<const InstanceListType*> a_imports = {&imports, &_InstanceListType};
  simpleAction<const InstanceListType*> a_sees = {&sees, &_InstanceListType};
  simpleAction<const InstanceListType*> a_extends = {&extends, &_InstanceListType};
  simpleAction<const Promotes*> a_promotes = {&promotes, &_Promotes};
  simpleAction<const Machine_Values*> a_values = {&values, &_Machine_Values};
  simpleAction<const Sets*> a_sets = {&sets, &_Sets};
  simpleAction<const IdentifierListType*> a_abstract_constants = {&abstractConstants, &_IdentifierListType};
  simpleAction<const VariablesType*> a_concrete_constants = {&concreteConstants, &_VariablesType};
  simpleAction<const IdentifierListType*> a_abstract_variables = {&abstractVariables, &_IdentifierListType};
  simpleAction<const VariablesType*> a_concrete_variables = {&concreteVariables, &_VariablesType};
  simpleAction<const Invariant*> a_properties = {&properties, &_Invariant};
  simpleAction<const Invariant*> a_invariant = {&invariant, &_Invariant};
  simpleAction<Initialisation*> a_initialisation = {&initialisation, &_Initialisation};
  simpleAction<Operations*> a_local_operations = {&localOperations, &_Operations};
  simpleAction<Operations*> a_operations = {&operations, &_Operations};
  simpleAction<const TypeInfos*> a_typeinfos = {&typeInfos, &_TypeInfos};

  Parser::workOnElements<
    const std::string*,
    const ParametersDeclaration*,
    const Machine_Values*,
    Operations*,
    const InstanceListType*,
    const Promotes*,
    const Invariant*,
    Initialisation*,
    const Sets*,
    const VariablesType*,    
    const TypeInfos*
    >(implementation, {
      {"Abstraction", a_abstraction},
      {"Parameters", a_parameters},
      {"Constraints", nullopt},
      {"Includes", a_includes},
      {"Sets", a_sets},
      {"Abstract_Constants", a_abstract_constants},
      {"Concrete_Constants", a_concrete_constants},
      {"Abstract_Variables", a_abstract_variables},
      {"Concrete_Variables", a_concrete_variables},
      {"Imports", a_imports},
      {"Sees", a_sees},
      {"Extends", a_extends},
      {"Promotes", a_promotes},
      {"Invariant", a_invariant},
      {"Initialisation", a_initialisation},
      {"Assertions", nullopt},
      {"Local_Operations",a_local_operations},
      {"Operations", a_operations},
      {"Properties", a_properties},
      {"TypeInfos", a_typeinfos},
      {"Values", a_values}
    },
      Parser::nonTranslatableYet);
      
    
    if (sees){
      std::vector<const ReferencedMachine*>  s_ref = sees -> referencedMachine;
      if (imports==NULL){
        imports = new InstanceListType;
      }
       std::vector<const ReferencedMachine*>& i_ref = const_cast<std::vector<const ReferencedMachine*>&>(imports->referencedMachine);
       i_ref.insert(i_ref.end(), s_ref.begin(), s_ref.end());
    };

    if (extends){
      std::vector<const ReferencedMachine*>  e_ref = extends -> referencedMachine;
      if (imports==NULL){
        imports = new InstanceListType;
      }
      std::vector<const ReferencedMachine*>& i_ref = const_cast<std::vector<const ReferencedMachine*>&>(imports->referencedMachine);
      i_ref.insert(i_ref.end(), e_ref.begin(), e_ref.end());
    };

    

    //sees works in the same way as import with public field but you cant modify the instance of import , but atelierb already do it 
    //even throught in atelierb you cant sees and import at the same time 

    
      //extends is equivalent to imports + promoted all, i take the decision to consider that the machine also import extended machines
      //even throught in atelierb you cant import and extends at the same time

}
