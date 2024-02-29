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

Printer::Printer(const std::filesystem::path &path, bool* const error)
    : path(path) {
  if (fs::exists(path)) {
    Input::err << path.string() << " already exists. Delete or move existing file before generating new one.\n";
    // Fatal error, but no exit now (we eventually want to write to other files...)
    *error = true;
    return;
  }

  codeStream = std::ofstream(path, std::ios::out);
  if (codeStream.fail()) {
    cerr << "Could not create file \"" << path.string() << "\"." << std::endl
         << "Check permissions." << std::endl;
    *error = true;
    return;
  }
}

Printer::~Printer() {
  // We close the file.
  codeStream.close();

  // We verify if there’s no error.
  if (codeStream.fail()) {
    cerr << "Error detected while closing file \"" << path.string() << "\"." << std::endl
         << "Contents may be corrupted." << std::endl;
    exit(ERR_OUTPUT_STREAM);
  }
}

void PrintAll(const std::string &name, const RustModule* const module) {
  // Create a stream for the output file.
  string filename {name};
  if (module->impl) {
    filename.append(".rs");
  } else {
    // base module
    filename.append("rs.template");
  }
  std::filesystem::path filepath;
  filepath = Input::output_dir / filename;

  bool error = false;
  Printer printer(filepath, &error);

  // We check there’s no error.
  if (error) {
    Input::err << "Error: error while creating the output files. b2rust stops there." << std::endl;
    exit(ERR_OUTPUT_STREAM);
  }

  // Do not format the output with `rustfmt` for now... It is no more in the needs of b2rust.
  const std::string code = module->PrintMe();
  printer.print(code);
}

void Printer::print(const std::string &code) {
  codeStream << code;
  codeStream.flush();
}
