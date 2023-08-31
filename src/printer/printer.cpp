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
#include "printer.h"

namespace fs = std::filesystem;

Printer::Printer(const std::string* const path_arg, bool* const error)
    : path(*path_arg) {
  // Before appending test, we want to verify the file does not already exist.
  const fs::path fpath = *path_arg;
  if (fs::exists(fpath)) {
    Input::err << "I want to output code to the `" << *path_arg
               << "` file, but it already exists. Nothing shall be written to this file. Please delete or move it before processing.\n";
    // Fatal error, but no exit now (we eventually want to write to other files...)
    *error = true;
    return;
  }

  codeStream = std::ofstream(*path_arg, std::ios::out);

  // It could be possible the opening failed, for example if we do not have permission.
  if (codeStream.fail()) {
    cerr << "Could not create file `" << *path_arg << "`! " << (codeStream.bad() ? "(Bad bit error.)" : "(Fail bit error.)")
         << " Does the directory exist? Do you have writing permissions to it?\n";
    *error = true;
    return;
  }
}

Printer::~Printer() {
  // We close the file.
  codeStream.close();

  // We verify if there’s no error.
  if (codeStream.fail()) {
    cerr << "Could not close file `" << path << "`! " << (codeStream.bad() ? "(Bad bit error.)" : "(Fail bit error.)")
         << " Code might have been appened to files, but do not rely on them!\n";
    exit(ERR_OUTPUT_STREAM);
  }
}

void PrintAll(const std::string* name, const RustModule* const module) {
  // Create a stream for the output file.
  std::string file;
  if (module->impl) {
    file = *Input::output_dir + *name + ".rs";
  } else {
    // base module
    file = *Input::output_dir + *name + ".rs.template";
  }

  bool error = false;
  Printer printer(&file, &error);

  // We check there’s no error.
  if (error) {
    Input::err << "Error: error while creating the output files. b2rust stops there." << std::endl;
    exit(ERR_OUTPUT_STREAM);
  }

  // Do not format the output with `rustfmt` for now... It is no more in the needs of b2rust.
  const std::string code = module->PrintMe();
  printer.print(&code);
}

void Printer::print(const std::string* const code) {
  codeStream << *code;
  codeStream.flush();
}
