#ifndef TIMELOCKER_STORAGE_H
#define TIMELOCKER_STORAGEMYSQL_H

#if __cplusplus >= 201703L
    #include <stdexcept>
    #include <string>
    #include <memory>

    #define throw(...)
    #include <cppconn/exception.h>
    #undef throw
#endif

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <string>
#include <mysql_connection.h>
#include "loggerDatabase.h"
#include "storage.h"

using std::string;

template <typename QuerySet, typename Logger>
class StorageMySQL: public AbstractDBManager<QuerySet, Logger> {
public:
    StorageMySQL();
    StorageMySQL(const StorageMySQL&) = delete;
    void operator=(StorageMySQL&) = delete;
    ~StorageMySQL();

    int connect(string host, string user, string password, string database, Logger*& loggerDB) override;
    int saveData(string key, string password, string deletionDate, Logger*& loggerDB) override;
    int getData(string key, QuerySet*& querySet, Logger*& loggerDB) override;
    bool isConnected() override { return _isConnectionStated; }
private:
    sql::Driver* _driver;
    sql::Connection* _connection;
    sql::Statement* _statement;
    sql::PreparedStatement* _preparedStatement;
    sql::ResultSet* _resultSet;
    bool _isConnectionStated;
};

template <typename QuerySet, typename Logger>
StorageMySQL<QuerySet, Logger>::StorageMySQL(): _driver(nullptr), _connection(nullptr),
                                     _statement(nullptr), _preparedStatement(nullptr),
                                     _resultSet(nullptr), _isConnectionStated(false) {
}

template <typename QuerySet, typename Logger>
int StorageMySQL<QuerySet, Logger>::connect(string host, string user,
                                            string password, string database,
                                            Logger*& loggerDB) {
    try {
        _driver = get_driver_instance();
        _connection = _driver->connect(host, user, password);
        _connection->setSchema(database);
        _isConnectionStated = true;
    } catch (sql::SQLException &exception) {
        _isConnectionStated = false;
        loggerDB->LogOperationConnect(database, _isConnectionStated, exception);
        return EXIT_FAILURE;
    }
    loggerDB->LogOperationConnect(database, _isConnectionStated);
    return EXIT_SUCCESS;
}

template <typename QuerySet, typename Logger>
StorageMySQL<QuerySet, Logger>::~StorageMySQL() {
    if (isConnected()) {
        _connection->close();
    }
    delete _connection;
}

template <typename QuerySet, typename Logger>
int StorageMySQL<QuerySet, Logger>::saveData(string key, string password, string deletionDate, Logger*& loggerDB) {
    if (!isConnected()) {
        loggerDB->LogOperationSaveData(key, _isConnectionStated);
        return EXIT_FAILURE;
    }
    try {
        _preparedStatement = _connection->prepareStatement("INSERT INTO "
                                                           "TimelockerStorage.Storage"
                                                           "(Storage.Key, Storage.Password, Storage.DeletionDate) "
                                                           "VALUES(?, ?, ?)");
        _preparedStatement->setString(1, key);
        _preparedStatement->setString(2, password);
        _preparedStatement->setString(3, deletionDate);
        _preparedStatement->execute();
        loggerDB->LogOperationSaveData(key, _isConnectionStated);
        delete _preparedStatement;
    } catch (sql::SQLException &exception) {
        loggerDB->LogOperationSaveData(key, _isConnectionStated, exception);
        delete _preparedStatement;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

template <typename QuerySet, typename Logger>
int StorageMySQL<QuerySet, Logger>::getData(string key, QuerySet*& querySet, Logger*& loggerDB) {
    if (!isConnected()) {
        loggerDB->LogOperationGetData(key, _isConnectionStated);
        return EXIT_FAILURE;
    }
    try {
        _statement = _connection->createStatement();
        _resultSet = _statement->executeQuery("SELECT Storage.Key, Password, DeletionDate "
                                              "FROM TimelockerStorage.Storage;");
        while (_resultSet->next()) {
            if (key == _resultSet->getString("Key")) {
                querySet->Insert("Key", key, true);
                querySet->Insert("Password", _resultSet->getString("Password"));
                querySet->Insert("DeletionDate", _resultSet->getString("DeletionDate"));
            }
        }
        delete _resultSet;
        delete _statement;
    } catch (sql::SQLException &exception) {
        loggerDB->LogOperationGetData(key, _isConnectionStated, exception);
        return EXIT_FAILURE;
    }
    loggerDB->LogOperationGetData(key, _isConnectionStated);
    return EXIT_SUCCESS;
}

#endif //TIMELOCKER_STORAGE_H
