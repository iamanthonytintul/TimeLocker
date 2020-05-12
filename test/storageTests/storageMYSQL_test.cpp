#include <iostream>
#include <gtest/gtest.h>
#include "resourceManagerDatabase.h"
#include "resourceManagerStringCreator.h"
#include "stringCreator.h"
#include "storageMYSQL.hpp"

const int amountOfDays = 7;

TEST(StorageMySQLTest, tryToConnect) {
    StorageMySQL<map<string, string>> database;
    ResourceManagerDatabase resourceManagerMySQLSuccess(PATH_TO_TEST_DB_CONFIG_OK);
    resourceManagerMySQLSuccess.parseFile();
    ResourceManagerDatabase resourceManagerMySQLError(PATH_TO_TEST_DB_CONFIG_NOT_OK);
    resourceManagerMySQLError.parseFile();
    EXPECT_EQ(database.connect(resourceManagerMySQLError.getHost(),
                                    resourceManagerMySQLError.getUser(),
                                    resourceManagerMySQLError.getPassword(),
                                    resourceManagerMySQLError.getDatabase()
                                   ), EXIT_FAILURE);
    EXPECT_EQ(database.connect(resourceManagerMySQLSuccess.getHost(),
                                    resourceManagerMySQLSuccess.getUser(),
                                    resourceManagerMySQLSuccess.getPassword(),
                                    resourceManagerMySQLSuccess.getDatabase()
                                   ), EXIT_SUCCESS);
}

TEST(StorageMYSQLTest, tryToSaveDataWhenConnected) {
    map<string, string> result;
    StorageMySQL<map<string, string>> database;
    ResourceManagerDatabase resourceManagerMySQL(PATH_TO_TEST_DB_CONFIG_OK);
    resourceManagerMySQL.parseFile();
    EXPECT_EQ(database.connect(resourceManagerMySQL.getHost(),
                                    resourceManagerMySQL.getUser(),
                                    resourceManagerMySQL.getPassword(),
                                    resourceManagerMySQL.getDatabase()
                                   ), EXIT_SUCCESS);
    ResourceManagerStringCreator resourceManagerStringCreator(PATH_TO_TEST_STRING_CREATOR);
    resourceManagerStringCreator.parseFile();
    StringCreator creator(resourceManagerStringCreator.getKeySize(),
                          resourceManagerStringCreator.getPasswordSize(),
                          resourceManagerStringCreator.getKeyStartSymbol(),
                          resourceManagerStringCreator.getKeyEndSymbol(),
                          resourceManagerStringCreator.getPasswordStartSymbol(),
                          resourceManagerStringCreator.getPasswordEndSymbol());
    string key;
    string password = creator.createPassword();
    string deletionDate = StringCreator::createDeletionDate(amountOfDays);

    do {
        key = creator.createKey();
        result = database.getData(key);
    } while (!result["Key"].empty());
    EXPECT_EQ(database.saveData(key, password, deletionDate), EXIT_SUCCESS);
    EXPECT_EQ(database.saveData(key, password, deletionDate), EXIT_FAILURE);
}

TEST(StorageMYSQLTest, tryToSaveDataWhenNotConnected) {
    map<string, string> result;
    StorageMySQL<map<string, string>> database;
    ResourceManagerDatabase resourceManagerMySQL(PATH_TO_TEST_DB_CONFIG_NOT_OK);
    resourceManagerMySQL.parseFile();
    EXPECT_EQ(database.connect(resourceManagerMySQL.getHost(),
                                    resourceManagerMySQL.getUser(),
                                    resourceManagerMySQL.getPassword(),
                                    resourceManagerMySQL.getDatabase()
                                   ), EXIT_FAILURE);
    ResourceManagerStringCreator resourceManagerStringCreator(PATH_TO_TEST_STRING_CREATOR);
    resourceManagerStringCreator.parseFile();
    StringCreator creator(resourceManagerStringCreator.getKeySize(),
                          resourceManagerStringCreator.getPasswordSize(),
                          resourceManagerStringCreator.getKeyStartSymbol(),
                          resourceManagerStringCreator.getKeyEndSymbol(),
                          resourceManagerStringCreator.getPasswordStartSymbol(),
                          resourceManagerStringCreator.getPasswordEndSymbol());
    string key;
    string password = creator.createPassword();
    string deletionDate = StringCreator::createDeletionDate(amountOfDays);

    do {
        key = creator.createKey();
        result = database.getData(key);
    } while (result["Key"] == key);
    EXPECT_EQ(database.saveData(key, password, deletionDate), EXIT_FAILURE);
}

TEST(StorageMYSQLTest, tryToGetData) {
    map<string, string> result;
    StorageMySQL<map<string, string>> database;
    ResourceManagerDatabase resourceManagerMySQL(PATH_TO_TEST_DB_CONFIG_OK);
    resourceManagerMySQL.parseFile();
    EXPECT_EQ(database.connect(resourceManagerMySQL.getHost(),
                                    resourceManagerMySQL.getUser(),
                                    resourceManagerMySQL.getPassword(),
                                    resourceManagerMySQL.getDatabase()
                                   ), EXIT_SUCCESS);
    ResourceManagerStringCreator resourceManagerStringCreator(PATH_TO_TEST_STRING_CREATOR);
    resourceManagerStringCreator.parseFile();
    StringCreator creator(resourceManagerStringCreator.getKeySize(),
                          resourceManagerStringCreator.getPasswordSize(),
                          resourceManagerStringCreator.getKeyStartSymbol(),
                          resourceManagerStringCreator.getKeyEndSymbol(),
                          resourceManagerStringCreator.getPasswordStartSymbol(),
                          resourceManagerStringCreator.getPasswordEndSymbol());
    string key;
    string password = creator.createPassword();
    string deletionDate = StringCreator::createDeletionDate(amountOfDays);

    do {
        key = creator.createKey();
        result = database.getData(key);
    } while (result["Key"] == key);
    EXPECT_EQ(result.empty(), NULL);
}

