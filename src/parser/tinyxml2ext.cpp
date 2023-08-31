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
#include "tinyxml2ext.h"








string QueryStringAttribute(XMLElement* const element, const string attribute, const string message) {
  const char* str;		// This one is fine.
  XMLError error = element->QueryStringAttribute(attribute.c_str(), &str);
  if (error != XML_SUCCESS) {
    cerr << message << "The error happened in the element " << element->Name() << ", with the searched attribute " << attribute << ". The error is the following: " << XMLDocument::ErrorIDToName(error) << " (error code " << error << ")." << endl;
    exit(ERR_BXML_CHECKING);
  }
  return str;
}


// Gets the text, throws an error if the first child of the element isn’t a `XMLText`.
const std::string* GetText(XMLElement* const element) {
  const char* const text = element->GetText(); // This one is fine.
  return new std::string(text);
}



XMLElement* FirstChildElement(XMLElement* root, const string& string) {
  return root->FirstChildElement(string.c_str());
}



XMLError LoadFile(XMLDocument* const document, const string& file) {
  return document->LoadFile(file.c_str());
}




ostream& operator<<(ostream& os, XMLElement* const element) {
  os << "It is a XMLElement whose name is " << element->Name() << ".\n";
  os << "Its attributes are:\n";
  for (const XMLAttribute* attr = element->FirstAttribute(); attr != NULL; attr = attr->Next()) os << "— The attribute " << attr->Name() << " which is " << attr->Value() << ".\n";

  os << "Its nodes are:\n";
  for (const XMLNode* attr = element->FirstChild(); attr != NULL; attr = attr->NextSibling()) {
    if (attr->ToElement()) {
      const XMLElement* const element = attr->ToElement();
      os << "— An element whose name is " << element->Name() << ".\n";
      os << "Its output: " << element;
    } else {
      os << "— A node which is not an element, a comment or a text...\n";
    }
  }
  return os;
}
