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
#ifndef H_TOOLS
#define H_TOOLS

#include <string>

class Tools {
public:
  /**
   * @brief Expands a tilde (`~`) character in the given path to the user's home directory.
   *
   * This function takes a path as input and replaces the leading tilde (`~`) character
   * with the absolute path to the user's home directory. If the input path does not
   * start with a tilde, it is returned unchanged.
   *
   * @param path The path containing a tilde to expand.
   * @return The expanded path.
   */
  static std::string expandTilde(const std::string& path);

  static std::string getLastWord(std::string wordsWithDot);

  static std::string getFirstWord(std::string wordsWithDot);
};

#endif
