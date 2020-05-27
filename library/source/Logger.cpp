#include "Logger.h"


Logger::Logger(const std::string& out){
    output.open(out);
}

Logger::~Logger() {
    output.close();
}

void Logger::warning(const std::string& out){
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    output << "--" << std::ctime(&end_time) << " [WARNING]" << out << std::endl;
}

void Logger::trace(const std::string& out){
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    output << "--" << std::ctime(&end_time) << " [TRACE]" << out << std::endl;
}

void Logger::debug(const std::string& out){
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    output << "--" << std::ctime(&end_time) << " [DEBUG]" << out << std::endl;
}

void Logger::info(const std::string& out){
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    output << "--" << std::ctime(&end_time) << " [INFO]" << out << std::endl;
}

void Logger::error(const std::string& out){
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    output << "--" << std::ctime(&end_time) << " [ERROR]" << out << std::endl;
}