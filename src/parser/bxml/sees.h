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
#ifndef H_SEES
#define H_SEES

#include "../parser.h"
#include "./referencedmachine.h"

#include <vector>
#include <tinyxml2.h>

//it is ambigous the bxml doc and the generated bxml, sees in theory should look differently but in practise it looks like exactly instancelisttype
class Sees {
  template <typename T> friend std::string* printIt(T*);
public:
  // --- ELEMENTS ---
  // min: 0, max: 1
  // Useless for now.


  /* min: 1, unbounded. */
  std::vector<const ReferencedMachine*> referencedMachine;


  // --- ATTRIBUTES ---
  
  // --- TOOLS ---
private:
  std::string* debugMe() const;
};

const Sees* _Sees(tinyxml2::XMLElement*);


#endif
