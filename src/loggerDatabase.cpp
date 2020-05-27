#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include "loggerDatabase.h"

namespace logging = boost::log;

LoggerDB::LoggerDB() {
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");
    logging::add_file_log(PATH_TO_DATABASE_LOG,
                          logging::keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] %Message%");
    logging::add_common_attributes();
}

void LoggerDB::LogOperationConnect(string_view database, bool isConnected, const sql::SQLException& exception) {
    if (isConnected) {
        BOOST_LOG_TRIVIAL(trace) << "Connection to database\"" << database << "\" is stated";
        return;
    }
    BOOST_LOG_TRIVIAL(error) << "SQLException in " << __FILE__;
    BOOST_LOG_TRIVIAL(error) << "(" << __FUNCTION__ << ") on line " << __LINE__;
    BOOST_LOG_TRIVIAL(error) << exception.what();
    BOOST_LOG_TRIVIAL(error) << "(MySQL error code: " << exception.getErrorCode()
                             << ", SQLState: " << exception.getSQLState() << ")";
    BOOST_LOG_TRIVIAL(error) << "Connection to database \""<< database << "\" is not stated";
}

void LoggerDB::LogOperationSaveData(string_view key, bool isConnected, const SQLException& exception) {
    BOOST_LOG_TRIVIAL(trace) << "Inserting data using key \"" << key << "\"";
    if (!isConnected) {
        BOOST_LOG_TRIVIAL(error) << "Connection to database is not stated";
        BOOST_LOG_TRIVIAL(error) << "Insertion failed";
        return;
    }
    if (exception.what()) {
        BOOST_LOG_TRIVIAL(error) << "SQLException in " << __FILE__;
        BOOST_LOG_TRIVIAL(error) << "(" << __FUNCTION__ << ") on line " << __LINE__;
        BOOST_LOG_TRIVIAL(error) << exception.what();
        BOOST_LOG_TRIVIAL(error) << "(MySQL error code: " << exception.getErrorCode()
                                 << ", SQLState: " << exception.getSQLState() << ")";
        BOOST_LOG_TRIVIAL(error) << "Insertion failed";
        return;
    }
    BOOST_LOG_TRIVIAL(trace) << "Insertion done";
}

void LoggerDB::LogOperationGetData(string_view key, bool isConnected, const SQLException& exception) {
    BOOST_LOG_TRIVIAL(trace) << "Getting data using key \"" << key << "\"";
    if (!isConnected) {
        BOOST_LOG_TRIVIAL(error) << "Connection to database is not stated";
        BOOST_LOG_TRIVIAL(error) << "Extraction failed";
        return;
    }
    if (exception.what()) {
        BOOST_LOG_TRIVIAL(error) << "SQLException in " << __FILE__;
        BOOST_LOG_TRIVIAL(error) << "(" << __FUNCTION__ << ") on line " << __LINE__;
        BOOST_LOG_TRIVIAL(error) << exception.what();
        BOOST_LOG_TRIVIAL(error) << "(MySQL error code: " << exception.getErrorCode()
                                 << ", SQLState: " << exception.getSQLState() << ")";
        BOOST_LOG_TRIVIAL(error) << "Extraction failed";
        return;
    }
    BOOST_LOG_TRIVIAL(trace) << "Extraction done";
}