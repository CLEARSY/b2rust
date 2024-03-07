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

#include "../util/report.h"

#include <fmt/format.h>


// Machine file for template functions.

template <typename T> void Parser::NodeActionForEachPresent(XMLElement* const root_element, const std::vector<std::tuple<std::string,
							     T,
							     void (*) (XMLElement*, T)>> actions) {
  auto it = actions.begin();

  for (XMLNode* node = root_element->FirstChild(); node != NULL; node = node->NextSibling()) {
    XMLElement* const element = node->ToElement();
    for (auto tmp_it = it; tmp_it != actions.end(); tmp_it++) {
      if (std::get<0>(*tmp_it) == element->Name()) {
	// We found an action associated with the element. We execute the action.
	(std::get<2>(*tmp_it))(element, std::get<1>(*tmp_it));
	// We change the `it` so that the loop is faster...
	it = tmp_it+1;
      }
    }
    // It wasn’t found.
  }
  // The element loop shall finish before the it loop finishes.
}


template <typename T> void Parser::NodeActionForEach(XMLElement* const element, T names, void (*action) (XMLElement*, T)) {
  for (XMLNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
    XMLElement* const element = node->ToElement();
    action(element, names);
  }
}

// template <typename T> void Parser::NodeActionForEachDifferent(XMLElement* const element, T object, const std::map<std::string, void (*) (XMLElement*, T)> actions) {
//   for (XMLNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
//     XMLElement* const element = node->ToElement();
//     actions.at(element->Name())(element, object);
//   }
// }

template <typename T> void Parser::NodeAction(XMLElement* const element, T object, void (*action) (XMLElement*, T)) {
  action(element->FirstChild()->ToElement(), object);
}


template <typename T, typename U> void Parser::NodeTwoActions(XMLElement* const element, T object1, U object2, void (*action1) (XMLElement*, T), void (*action2) (XMLElement*, U)) {
  XMLNode* first = element->FirstChild();
  action1(first->ToElement(), object1);
  action2(first->NextSibling()->ToElement(), object2);
}


template <typename... Ts>
void Parser::workOnElements(XMLElement* const element,
			    std::map<std::string, elementAction<Ts...>> actions,
			    const std::string ) {
  for (XMLNode* node = element->FirstChild(); node != NULL; node = node->NextSibling()) {
    XMLElement* const subelement = node->ToElement();
    std::string name = subelement->Name();
    auto it = actions.find(name);
    if (it == actions.end()) {
      // The element isn’t on the list of recognized elements of b2rust.
      Report::emitError(fmt::format("{};forbidden child {} for BXML element {}", name, element->Name()));
      Checker::checking_error = true;
    } else {
      elementAction<Ts...> action = it->second;
      // Needs to be improved are the tests are done several times.
      if (action.has_value()) {
	// We want an action.
	([&] {
	  if (std::holds_alternative<simpleAction<Ts>>(*action)) {
	    simpleAction<Ts> s = std::get<simpleAction<Ts>>(*action);
	    *s.first = s.second(subelement);
	  } else {
	    if (std::holds_alternative<vectorAction<Ts>>(*action)) {
	      vectorAction<Ts> v = std::get<vectorAction<Ts>>(*action);
	      v.first->push_back(v.second(subelement));
	    }
	  }	
	}(), ...);
      }
    }
  }  
}
