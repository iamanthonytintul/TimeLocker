#include <iostream>
#include <gtest/gtest.h>
#include "storageMYSQL.hpp"

#define KEY "UniqueName"
#define PASSWORD "CorrectPassword"
#define DATE "2020-03-01"

TEST(StorageMYSQL, saveData_valid) {
    map<string, string> result;
    StorageMySQL<map<string, string>> database;
    result = database.getData(KEY);
    if (result["Key"] == KEY) {
        EXPECT_EQ(database.saveData(KEY, PASSWORD, DATE), EXIT_FAILURE);
    } else {
        EXPECT_EQ(database.saveData(KEY, PASSWORD, DATE), EXIT_SUCCESS);
    }
}
