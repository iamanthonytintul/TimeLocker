#ifndef TIMELOCKER_STORAGE_H
#define TIMELOCKER_STORAGEMYSQL_H

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <string>
#include <map>
#include "includes/storage.h"

#define HOST "localhost"
#define USER "dansik"
#define PASS "1234"
#define DATABASE "TimelockerStorage"

using std::cout;
using std::endl;
using std::map;
using std::string;

template <typename DBRow>
class StorageMySQL: public AbstractDBManager<DBRow> {
public:
    StorageMySQL();
    ~StorageMySQL() override;
    int saveData(string key, string password, string deletionDate) override;
    DBRow getData(string key) override;
    bool isConnected() override { return _isConnectionStated; }
private:
    sql::Driver* _driver;
    sql::Connection* _connection;
    sql::Statement* _statement;
    sql::PreparedStatement* _preparedStatement;
    sql::ResultSet* _resultSet;
    bool _isConnectionStated;
};

template <typename DBRow>
StorageMySQL<DBRow>::StorageMySQL(): _statement(nullptr), _resultSet(nullptr), _preparedStatement(nullptr) {
    cout << endl;
    cout << "Connecting to database " << DATABASE << "..." << endl;
    try {
        _driver = get_driver_instance();
        _connection = _driver->connect(HOST, USER, PASS);
        _connection->setSchema(DATABASE);

        _isConnectionStated = true;
        cout << "Connection to database \"" << DATABASE <<"\" is stated." << endl;
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

        _isConnectionStated = false;
        cout << "Connection to database \""<< DATABASE << "\" is not stated." << endl;
    }
    cout << endl;
}

template <typename DBRow>
StorageMySQL<DBRow>::~StorageMySQL() {
    cout << "Closing connection to database \"" << DATABASE << "\"..." << endl;
    if (isConnected()) {
        _connection->close();
        delete _connection;
        cout << "Connection to database \"" << DATABASE << "\" is closed." << endl;
    } else {
        cout << "No connection to close." << endl;
    }
    cout << endl;
}

template <typename DBRow>
int StorageMySQL<DBRow>::saveData(string key, string password, string deletionDate) {

    if (!isConnected()) {
        cout << "Error: "
                "connection to database \"" << DATABASE << "\" is not stated." << endl;
        cout << "Insertion failed." << endl;
        return EXIT_FAILURE;
    }

    try {
        cout << endl << "Inserting data..." << endl;
        _preparedStatement = _connection->prepareStatement("INSERT INTO "
                                                           "TimelockerStorage.Storage"
                                                           "(Storage.Key, Storage.Password, Storage.DeletionDate) "
                                                           "VALUES(?, ?, ?)");
        _preparedStatement->setString(1, key);
        _preparedStatement->setString(2, password);
        _preparedStatement->setString(3, deletionDate);
        _preparedStatement->execute();

        delete _preparedStatement;
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;

        cout << "Insertion failed." << endl;
        delete _preparedStatement;
        return EXIT_FAILURE;
    }
    cout << "Insertion done." << endl;
    return EXIT_SUCCESS;
}

template <typename DBRow>
DBRow StorageMySQL<DBRow>::getData(string key) {
    map<string, string> result;

    if (!isConnected()) {
        cout << "Error: "
                "connection to database \"" << DATABASE << "\" is not stated." << endl;
        cout << "Extraction failed." << endl;
        return result;
    }

    try {
        cout << endl << "Getting data using key \"" << key << "\"..." << endl;
        _statement = _connection->createStatement();
        _resultSet = _statement->executeQuery("SELECT Storage.Key, Password, DeletionDate "
                                              "FROM TimelockerStorage.Storage;");
        while (_resultSet->next()) {
            if (key == _resultSet->getString("Key")) {
                result.insert({"Key", key});
                result.insert({"Password", _resultSet->getString("Password")});
                result.insert({"DeletionDate", _resultSet->getString("DeletionDate")});
                break;
            }
        }
        delete _resultSet;
        delete _statement;
        cout << "Extraction done." << endl;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        cout << "Extraction failed." << endl;
    }
    return result;
}

#endif //TIMELOCKER_STORAGE_H
