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
#ifndef H_BXMLELEMENT
#define H_BXMLELEMENT

// This document aims at, generally, improving `tinyxml2`, either with extension function, or by redefining functions which parse `char` star arguments into `std::string`, for example.
// At first, the goal was to extend the classes (XMLElement, XMLDocument) with inheritance, but it was impossible because the XMLElement class cannot be inherited (private destructor) and it was quite clumsy (diamond problem because e.g. BXMLDocument class would have needed to inherit from BXMLNode and XMLDocument which couldn’t be resolved by the `virtual` method, so, need to override special added functions in each new class...)


#include <tinyxml2.h>
#include <string>

#include "../error_codes.h"
#include <map>
#include <functional>

#define METHOD(function) [=](XMLElement* a) {this->function(a);}


using namespace std;
using namespace tinyxml2;





// Returns a string instead of an error. In case of error, it needs to take as argument the message to write. The message shouldn’t include information on the element, which are printed by the function. It should end by a new line.
string QueryStringAttribute(XMLElement* const, const string attribute, const string message);

const std::string* GetText(XMLElement*);

// `FirstChildElement`, but with strings.
XMLElement* FirstChildElement(XMLElement*, const string&);

// `LoadFile`, but with strings.
XMLError LoadFile(XMLDocument* const, const string&);


// The TinyXML2 debug functions.
ostream& operator<<(ostream& os, XMLElement*);


#endif
