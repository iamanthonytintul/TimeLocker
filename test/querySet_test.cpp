#include <gtest/gtest.h>
#include "querySet.h"
#include "resourceManagerStringCreator.h"
#include "stringCreator.h"

const int COLUMNS_IN_ROW = 3;
const int AMOUNT_OF_ROWS = 5;

class TestStringCreator: public ::testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;
    StringCreator* creator{nullptr};
};

void TestStringCreator::SetUp() {
    ResourceManagerStringCreator resourceManagerStringCreator(PATH_TO_TEST_STRING_CREATOR);
    resourceManagerStringCreator.parseFile();
    creator = new StringCreator(resourceManagerStringCreator.getKeySize(),
                          resourceManagerStringCreator.getPasswordSize(),
                          resourceManagerStringCreator.getKeyStartSymbol(),
                          resourceManagerStringCreator.getKeyEndSymbol(),
                          resourceManagerStringCreator.getPasswordStartSymbol(),
                          resourceManagerStringCreator.getPasswordEndSymbol());
}

void TestStringCreator::TearDown() {
    delete creator;
}

TEST_F(TestStringCreator, QuerySetRow) {
    QuerySet querySet;
    map<string, string> result;
    map<string, string> databaseRow;
    bool newRow = true;
    for (int i = 0; i < COLUMNS_IN_ROW; i++) {
        std::string key = creator->createKey();
        databaseRow[key] = creator->createPassword();
        querySet.Insert(key, databaseRow[key], newRow);
        result = querySet.GetQuerySetRow();
        EXPECT_EQ(databaseRow[key], result[key]);
        newRow = false;
    }
}

TEST_F(TestStringCreator, QuerySet) {
    QuerySet querySet;
    vector<map<string, string>> result;
    vector<map<string, string>> databaseRows;
    vector<string> keys;
    string key;
    for (int row = 0; row < AMOUNT_OF_ROWS; row++) {
        bool newRow = true;
        databaseRows.resize(databaseRows.size() + 1);
        for (int column = 0; column < COLUMNS_IN_ROW; column++) {
            key = creator->createKey();
            databaseRows.back()[key] = creator->createPassword();
            keys.push_back(key);
            querySet.Insert(key, databaseRows[databaseRows.size() - 1][key], newRow);
            newRow = false;
        }
    }
    result = querySet.GetQuerySet();
    for (int row = 0; row < AMOUNT_OF_ROWS; row++) {
        for (int column = 0; column < COLUMNS_IN_ROW; column++) {
            key = keys[row * column + column];
            EXPECT_EQ(databaseRows[row][key], result[row][key]);
        }
    }
}
