#include <iostream>
#include <gtest/gtest.h>
#include "includes/stringCreator.h"
#include "storageMYSQL.hpp"

const int amountOfDays = 7;

TEST(StorageMySQLTest, connection) {
    StorageMySQL<map<string, string>> database;
    EXPECT_EQ(database.connect("", "", "", ""), EXIT_FAILURE);
    EXPECT_EQ(database.connect("localhost", "dansik",
            "1234", "TimelockerStorage"), EXIT_SUCCESS);
}

TEST(StorageMYSQLTest, saveDataIsConnected) {
    map<string, string> result;
    StorageMySQL<map<string, string>> database;
    EXPECT_EQ(database.connect("localhost", "dansik",
                               "1234", "TimelockerStorage"), EXIT_SUCCESS);
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
    EXPECT_EQ(database.connect("", "",
                               "", ""), EXIT_FAILURE);
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

TEST(StorageMYSQLTest, getDataIsConnected) {
    map<string, string> result;
    StorageMySQL<map<string, string>> database;
    EXPECT_EQ(database.connect("localhost", "dansik",
                               "1234", "TimelockerStorage"), EXIT_SUCCESS);
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

TEST(StorageMYSQLTest, getDataIsNotConnected) {
    map<string, string> result;
    StorageMySQL<map<string, string>> database;
    EXPECT_EQ(database.connect("", "",
                               "", ""), EXIT_FAILURE);
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
