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
#include "case_sub.h"

Choices* _Choices(XMLElement* element) {

  Choices* _choices = new Choices;

  vectorAction<Choice*> a_choice = {&_choices -> choices, &_Choice};

  Parser::workOnElements<
    Choice*
    >(element,{
        {"Choice", a_choice}
    },
    Parser::uncompliant);

  return _choices;

}


Choice* _Choice(XMLElement* element){
  Choice* _choice = new Choice;

 
    vectorAction<const ExpressionType*> a_value = {&_choice->value, &_ExpressionType};
    simpleAction<SubstitutionType*> a_then = {&_choice->then, &_SubstitutionType};

    Parser::workOnElements<
      const ExpressionType*,
      SubstitutionType*
      >(element, {
    {"Value", a_value},
    {"Then", a_then}
    },
    Parser::uncompliant);

    return _choice;
}


Instruction* _CaseSub(XMLElement* element) {
  CaseSub* _case = new CaseSub;

  simpleAction<const ExpressionType*> a_value = {&_case -> value, &_ExpressionType};
  simpleAction<Choices*> a_choices = {&_case -> choices, &_Choices};
  simpleAction<SubstitutionType*> a_else = {&_case -> _else, &_SubstitutionType};


    
    Parser::workOnElements<
      const ExpressionType*,
      Choices*,
      SubstitutionType*
      >(element,{
      {"Value", a_value},
      {"Choices", a_choices},
      {"Else", a_else}
    },
    Parser::uncompliant);;

    return _case;
}
