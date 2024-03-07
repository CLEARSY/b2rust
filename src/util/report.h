#ifndef UTIL_REPORT_H
#define UTIL_REPORT_H

#include<string>

namespace Report {

enum class Level { INFO, WARNING, ERROR, FATAL };

using std::string;

extern void emit(Level level, const string& msg, int code=EXIT_FAILURE);
extern void emitInfo(const string& msg);
extern void emitWarning(const string& msg);
extern void emitError(const string& msg);
extern void startExecution(const string& component);
extern void fatalError(const string& error, int code);
extern void endExecution(int code);

};

#endif // UTIL_REPORT.H

