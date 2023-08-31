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
#ifndef H_IO
#define H_IO

#include <iostream>

typedef enum b2rustError {
  // The program behaved as expected. This does not mean no error occurred, but if an error occurred, it did not concern the conversion (= the conversion would have been the same even without this error and is likely correct).
  OK = 0,

  // The call syntax of the program was not respected.
  ERR_SYNTAX = 1,
  // The output file could not be created, or could not be opened with the write permission.
  ERR_OUTPUT_FILE = 2,
  // Could not write to output stream. R/W or logical error on I/O operation. Elsewise, no output without --force option. A file already exists.
  ERR_OUTPUT_STREAM = 3,

  // The BXML file could not be loaded.
  ERR_BXML_LOADING = 10,
  // Cannot get text of element.
  ERR_BXML_GETTEXT = 11,
  ERR_BXML_PARSING = 12,
  
  // An error occurred during the BXML checking. There’s at least one error. Either the file is not BXML complient, or an element cannot be converted yet.
  ERR_BXML_CHECKING = 20,
  // An error occurred during the conversion. The file is BXML complient and all its elements can be converted, but an element is lacking to allow the conversion. Do your files represent a verified B~program? If yes, it is a b2rust error.
  ERR_BXML_LACK = 21,

  // It is a b2rust internal error. Please report this bug.
  ERR_B2RUST = 31,
} b2rustError;

#endif
