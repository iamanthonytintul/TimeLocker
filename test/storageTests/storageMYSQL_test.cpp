#include <iostream>
#include <gtest/gtest.h>
#include "includes/stringCreator.h"
#include "storageMYSQL.hpp"

#define amountOfDays 7

TEST(StorageMYSQLTest, saveDataCheckSingleRequest) {
    map<string, string> result;
    StorageMySQL<map<string, string>> database;
    database.connect();
    StringCreator creator;
    string key;
    string password = creator.createPassword();
    string deletionDate = creator.createDeletionDate(amountOfDays);

    do {
        key = creator.createKey();
        result = database.getData(key);
    } while (result["Key"] == key);

    if (!database.isConnected()) {
        EXPECT_EQ(database.saveData(key, password, deletionDate), EXIT_FAILURE);
    } else {
        EXPECT_EQ(database.saveData(key, password, deletionDate), EXIT_SUCCESS);
    }
}

TEST(StorageMYSQLTest, saveDataCheckMultipleRequestOneKey) {
    map<string, string> result;
    StorageMySQL<map<string, string>> database;
    database.connect();
    StringCreator creator;
    string key;
    string password = creator.createPassword();
    string deletionDate = creator.createDeletionDate(amountOfDays);

    do {
        key = creator.createKey();
        result = database.getData(key);
    } while (result["Key"] == key);

    if (!database.isConnected()) {
        EXPECT_EQ(database.saveData(key, password, deletionDate), EXIT_FAILURE);
    } else {
        EXPECT_EQ(database.saveData(key, password, deletionDate), EXIT_SUCCESS);
        EXPECT_EQ(database.saveData(key, password, deletionDate), EXIT_FAILURE);
    }
}


TEST(StorageMYSQLTest, saveDataCheckMultipleRequestMultipleKey) {
    map<string, string> result;
    StorageMySQL<map<string, string>> database;
    database.connect();
    StringCreator creator;
    string keyOne;
    string keyTwo;
    string keyThree;
    string password = creator.createPassword();
    string deletionDate = creator.createDeletionDate(amountOfDays);

    do {
        keyOne = creator.createKey();
        result = database.getData(keyOne);
    } while (result["Key"] == keyOne);

    do {
        keyTwo = creator.createKey();
        result = database.getData(keyTwo);
    } while (result["Key"] == keyTwo);

    do {
        keyThree = creator.createKey();
        result = database.getData(keyThree);
    } while (result["Key"] == keyThree);

    if (!database.isConnected()) {
        EXPECT_EQ(database.saveData(keyOne, password, deletionDate), EXIT_FAILURE);
        EXPECT_EQ(database.saveData(keyTwo, password, deletionDate), EXIT_FAILURE);
        EXPECT_EQ(database.saveData(keyThree, password, deletionDate), EXIT_FAILURE);
    } else {
        EXPECT_EQ(database.saveData(keyOne, password, deletionDate), EXIT_SUCCESS);
        EXPECT_EQ(database.saveData(keyOne, password, deletionDate), EXIT_FAILURE);
        EXPECT_EQ(database.saveData(keyTwo, password, deletionDate), EXIT_SUCCESS);
        EXPECT_EQ(database.saveData(keyThree, password, deletionDate), EXIT_SUCCESS);
        EXPECT_EQ(database.saveData(keyTwo, password, deletionDate), EXIT_FAILURE);
        EXPECT_EQ(database.saveData(keyThree, password, deletionDate), EXIT_FAILURE);
    }
}
