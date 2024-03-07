#include "report.h"
#include "../input.h"

#include<iostream>
#include<fmt/format.h>

namespace Report {

    using std::cerr;
    using std::cout;

  void emit(Level level, const string &text, int code) {
    switch(level) {
      case Level::INFO: {
        emitInfo(text);
        break;
      }
      case Level::WARNING: {
          emitWarning(text);
          break;
      }
      case Level::ERROR: {
        emitError(text);
        break;
      }
      case Level::FATAL: {
        fatalError(text, code);
        break;
      }
    }
  }

  void emitInfo (const string &text) {
      if (Input::xmlOutput) {
        cout << fmt::format("  <info message = '{}'/>\n", text);
      }
      else {
        cerr << fmt::format("{}\n", text);
      }
  }

  void emitWarning (const string &text) {
      if (Input::xmlOutput) {
        cout << fmt::format("  <warning message = '{}'/>\n", text);
      }
      else {
        cerr << fmt::format("{}\n", text);
      }
  }

  void emitError (const string &text) {
      if (Input::xmlOutput) {
        cout << fmt::format("  <error message = '{}'/>\n", text);
      }
      else {
        cerr << "\x1B[37m" << fmt::format("Error: {}", text) << "\033[0m" << std::endl;
      }
  }

  void fatalError (const string &text, int code) {
    emitError(text);
    endExecution(code);
  }

  void startExecution (const string &component) {
    if (Input::xmlOutput) {
        cout << fmt::format("<b2rust component='{}'>\n", component);
    }
    else {
        cout << fmt::format("b2rust execution started on component {}.\n", component);
    }
  }

  void endExecution (int code) {
      if (Input::xmlOutput) {
        std::cout << "</b2rust>\n";
      }
      exit(code);
  }

}; // namespace ends
