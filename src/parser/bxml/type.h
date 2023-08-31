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
#ifndef H_TYPE
#define H_TYPE

#include "tinyxml2.h"
#include "../parser.h"

#include <string>
#include <vector>
#include <map>


class Type {
  template <typename T> friend std::string* printIt(T*);
public:
  // --- ELEMENTS ---
  // min: 0, unbounded.
  // std::vector<const RustType*> type;

  // --- TOOLS ---
private:
  virtual std::string* debugMe() const = 0;
};


class Type_BinaryExp : public Type {
  template <typename T> friend std::string* printIt(T*);
public:
  // --- ELEMENTS ---
  // exactly 2.
  std::vector<const Type*> type;

  // --- ATTRIBUTES ---
  // required.
  const std::string* op;

    // --- TOOLS ---
private:
  std::string* debugMe() const;
};

const Type* _Type_BinaryExp(tinyxml2::XMLElement*);


class Type_Id : public Type {
  template <typename T> friend std::string* printIt(T*);
public:
  // --- ATTRIBUTES ---
  // required.
  const std::string* value;

  // --- TOOLS ---
private:
  std::string* debugMe() const;
};

const Type* _Type_Id(tinyxml2::XMLElement*);


class Type_UnaryExp : public Type {
  template <typename T> friend std::string* printIt(T*);
public:
  // --- ELEMENTS ---
  // exactly one.
  const Type* type;
  
  // --- ATTRIBUTES ---
  // required.
  const std::string* op;

  // --- TOOLS ---
private:
  std::string* debugMe() const;
};

const Type* _Type_UnaryExp(tinyxml2::XMLElement*);


class Type_Struct_RecordItem {
  template <typename T> friend std::string* printIt(T*);
public:
  // --- ELEMENTS ---
  // exactly one.
  const Type* type;

  // --- ATTRIBUTES ---
  // required.
  const std::string* label;
  
  // --- TOOLS ---
private:
  std::string* debugMe() const;
};

const Type_Struct_RecordItem* _Type_Struct_RecordItem(tinyxml2::XMLElement*);


class Type_Struct : public Type {
  template <typename T> friend std::string* printIt(T*);
public:
  // --- ELEMENTS ---
  // exactly one.
  const Type_Struct_RecordItem* recordItem;
  
  // --- TOOLS ---
private:
  std::string* debugMe() const;
};

const Type* _Type_Struct(tinyxml2::XMLElement*);


// Is void.
class Type_GenericType : public Type {
  template <typename T> friend std::string* printIt(T*);
  std::string* debugMe() const;
};

const Type* _Type_GenericType(tinyxml2::XMLElement*);

#include "type.tcc"

#endif
