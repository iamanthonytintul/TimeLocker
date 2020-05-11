#include <iostream>
#include <gtest/gtest.h>
#include "stringCreator.h"
#include "resourseManagerDatabase.h"
#include "storageMYSQL.hpp"

const int amountOfDays = 7;

TEST(StorageMySQLTest, connection) {
    StorageMySQL<map<string, string>> database;
    ResourceManagerDatabase resourceManagerMySqlSUCCESS(PATH_TO_TEST_DB_CONFIG_OK);
    resourceManagerMySqlSUCCESS.parseFile();
    ResourceManagerDatabase resourceManagerMySqlERROR(PATH_TO_TEST_DB_CONFIG_NOT_OK);
    resourceManagerMySqlERROR.parseFile();
    EXPECT_EQ(database.connect(resourceManagerMySqlERROR.getHost(),
                                    resourceManagerMySqlERROR.getUser(),
                                    resourceManagerMySqlERROR.getPassword(),
                                    resourceManagerMySqlERROR.getDatabase()
                                   ), EXIT_FAILURE);
    EXPECT_EQ(database.connect(resourceManagerMySqlSUCCESS.getHost(),
                                    resourceManagerMySqlSUCCESS.getUser(),
                                    resourceManagerMySqlSUCCESS.getPassword(),
                                    resourceManagerMySqlSUCCESS.getDatabase()
                                   ), EXIT_SUCCESS);
}

TEST(StorageMYSQLTest, saveDataIsConnected) {
    map<string, string> result;
    StorageMySQL<map<string, string>> database;
    ResourceManagerDatabase resourceManagerMySqlSUCCESS(PATH_TO_TEST_DB_CONFIG_OK);
    resourceManagerMySqlSUCCESS.parseFile();
    EXPECT_EQ(database.connect(resourceManagerMySqlSUCCESS.getHost(),
                                    resourceManagerMySqlSUCCESS.getUser(),
                                    resourceManagerMySqlSUCCESS.getPassword(),
                                    resourceManagerMySqlSUCCESS.getDatabase()
                                   ), EXIT_SUCCESS);
    StringCreator creator;
    string key;
    string password = creator.createPassword();
    string deletionDate = creator.createDeletionDate(amountOfDays);

    do {
        key = creator.createKey();
        result = database.getData(key);
    } while (result["Key"] == key);
    EXPECT_EQ(database.saveData(key, password, deletionDate), EXIT_SUCCESS);
    EXPECT_EQ(database.saveData(key, password, deletionDate), EXIT_FAILURE);
}

TEST(StorageMYSQLTest, saveDataIsNotConnected) {
    map<string, string> result;
    StorageMySQL<map<string, string>> database;
    ResourceManagerDatabase resourceManagerMySqlERROR(PATH_TO_TEST_DB_CONFIG_NOT_OK);
    resourceManagerMySqlERROR.parseFile();
    EXPECT_EQ(database.connect(resourceManagerMySqlERROR.getHost(),
                                    resourceManagerMySqlERROR.getUser(),
                                    resourceManagerMySqlERROR.getPassword(),
                                    resourceManagerMySqlERROR.getDatabase()
                                   ), EXIT_FAILURE);
    StringCreator creator;
    string key;
    string password = creator.createPassword();
    string deletionDate = creator.createDeletionDate(amountOfDays);

    do {
        key = creator.createKey();
        result = database.getData(key);
    } while (result["Key"] == key);
    EXPECT_EQ(database.saveData(key, password, deletionDate), EXIT_FAILURE);
}

TEST(StorageMYSQLTest, getData) {
    map<string, string> result;
    StorageMySQL<map<string, string>> database;
    ResourceManagerDatabase resourceManagerMySqlSUCCESS(PATH_TO_TEST_DB_CONFIG_OK);
    resourceManagerMySqlSUCCESS.parseFile();
    EXPECT_EQ(database.connect(resourceManagerMySqlSUCCESS.getHost(),
                                    resourceManagerMySqlSUCCESS.getUser(),
                                    resourceManagerMySqlSUCCESS.getPassword(),
                                    resourceManagerMySqlSUCCESS.getDatabase()
                                   ), EXIT_SUCCESS);
    StringCreator creator;
    string key;
    string password = creator.createPassword();
    string deletionDate = creator.createDeletionDate(amountOfDays);

    do {
        key = creator.createKey();
        result = database.getData(key);
    } while (result["Key"] == key);
    EXPECT_EQ(result.empty(), NULL);
}

