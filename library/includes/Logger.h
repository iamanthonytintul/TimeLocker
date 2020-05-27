
#ifndef BACKENDSERVICE_LOGGER_H
#define BACKENDSERVICE_LOGGER_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

struct Logger {
    Logger() = default;
    Logger(const std::string& out);
    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;
    void warning(const std::string&);
    void trace(const std::string&);
    void debug(const std::string&);
    void info(const std::string&);
    void error(const std::string&);
    ~Logger();
private:
    std::ofstream output;
};

#endif //BACKENDSERVICE_LOGGER_H
