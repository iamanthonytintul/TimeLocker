#ifndef TIMELOCKER_LOGGERDATABASE_H
#define TIMELOCKER_LOGGERDATABASE_H

#if __cplusplus >= 201703L
#include <stdexcept>
#include <string>
#include <memory>

#define throw(...)
#include <cppconn/exception.h>
#undef throw
#endif

#include <cppconn/exception.h>
#include <string>

using sql::SQLException;
using std::string_view;

struct LoggerDB {
public:
    LoggerDB();
    LoggerDB(const LoggerDB&) = delete;
    void operator=(const LoggerDB&) = delete;
    void LogOperationConnect(string_view database, bool isConnected, const SQLException& exception = SQLException());
    void LogOperationSaveData(string_view key, bool isConnected, const SQLException& exception = SQLException());
    void LogOperationGetData(string_view key, bool isConnected, const SQLException& exception = SQLException());
};

#endif //TIMELOCKER_LOGGERDATABASE_H
