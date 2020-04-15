#include <gmock/gmock.h>
#include <iostream>
#include "storage.h"
#define SUCCESS 0
using ::testing::_;
using ::testing::SetArgReferee;
using ::testing::DoAll;
using ::testing::Return;

class MockDataBase: public IDBManager {
public:
    MOCK_METHOD4(saveData, int(std::string path, std::string link, std::string key, std::string date));
    MOCK_METHOD1(getData, std::string(std::string link));
    MOCK_METHOD1(deleteData, bool(std::string link));
};

TEST(Storage, getPathToFileTest) {
    std::string path = "/usr/bin/file.txt";
    std::string link = "google.com/download/file.txt";
    std::string result = "someinfo";
    auto* database = new MockDataBase();
    EXPECT_CALL(*database,
            getData(link))
            .WillRepeatedly(Return(result));
    auto* storage = new Storage<MockDataBase>(database);
    EXPECT_EQ(storage->getPathToFile(link), path);
    delete database;
    delete storage;
}

TEST(Storage, isUniqueLink) {
    std::string link = "google.com/download/file.txt";
    std::string result = "someinfo";
    auto* database = new MockDataBase();
    EXPECT_CALL(*database,
                getData(link))
            .WillRepeatedly(Return(result));
    auto* storage = new Storage<MockDataBase>(database);
    EXPECT_TRUE(storage->isUniqueLink(link));
    delete database;
    delete storage;
}

TEST(Storage, isValidLink) {
    std::string link = "google.com/download/file.txt";
    std::string result = "someinfo";
    auto* database = new MockDataBase();
    EXPECT_CALL(*database,
                getData(link))
            .WillRepeatedly(Return(result));
    auto* storage = new Storage<MockDataBase>(database);
    EXPECT_TRUE(storage->isValidLink(link));
    delete database;
    delete storage;
}

TEST(Storage, isCorrectKey) {
    std::string link = "google.com/download/file.txt";
    std::string key = "key1337";
    std::string result = "someinfo";
    auto* database = new MockDataBase();
    EXPECT_CALL(*database,
                getData(link))
            .WillRepeatedly(Return(result));
    auto* storage = new Storage<MockDataBase>(database);
    EXPECT_TRUE(storage->isCorrectKey(link, key));
    delete database;
    delete storage;
}

TEST(StorageDateInspector, checkDeletionDate) {
    std::string link = "google.com/download/file.txt";
    std::string result = "someinfo";
    auto* database = new MockDataBase();
    EXPECT_CALL(*database,
                getData(link))
            .WillRepeatedly(Return(result));
    auto* storageDateInspector = new StorageDateInspector<MockDataBase>(database);
    EXPECT_EQ(storageDateInspector->checkDeletionDate(link), SUCCESS);
    delete storageDateInspector;
    delete database;
}