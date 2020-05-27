#include <gtest/gtest.h>
#include "loggerDatabase.h"
#include "querySet.h"
#include "resourceManagerDatabase.h"
#include "resourceManagerStringCreator.h"
#include "stringCreator.h"
#include "storageMYSQL.hpp"

const int amountOfDays = 7;

class TestResourceManagerDatabase: public ::testing::Test{
protected:
    void SetUp() override;
    void TearDown() override;
    LoggerDB* logger{nullptr};
    ResourceManagerDatabase* resourceManagerDatabaseERROR{nullptr};
    ResourceManagerDatabase* resourceManagerDatabaseSUCCESS{nullptr};
};

void TestResourceManagerDatabase::SetUp() {
    logger = new LoggerDB;
    resourceManagerDatabaseERROR = new ResourceManagerDatabase(PATH_TO_TEST_DB_CONFIG_NOT_OK);
    resourceManagerDatabaseERROR->parseFile();
    resourceManagerDatabaseSUCCESS = new ResourceManagerDatabase(PATH_TO_TEST_DB_CONFIG_OK);
    resourceManagerDatabaseSUCCESS->parseFile();
}

void TestResourceManagerDatabase::TearDown() {
    delete logger;
    delete resourceManagerDatabaseERROR;
    delete resourceManagerDatabaseSUCCESS;
}

class TestDatabaseUtils: public ::testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;
    LoggerDB* logger{nullptr};
    QuerySet* querySet{nullptr};
    ResourceManagerDatabase* resourceManagerDatabase{nullptr};
    StorageMySQL<QuerySet, LoggerDB>* database{nullptr};
    StringCreator* creator{nullptr};
};

void TestDatabaseUtils::SetUp() {
    querySet = new QuerySet;
    logger = new LoggerDB;
    resourceManagerDatabase = new ResourceManagerDatabase(PATH_TO_TEST_DB_CONFIG_OK);
    resourceManagerDatabase->parseFile();
    ResourceManagerStringCreator resourceManagerStringCreator(PATH_TO_TEST_STRING_CREATOR);
    resourceManagerStringCreator.parseFile();
    creator = new StringCreator(resourceManagerStringCreator.getKeySize(),
                                resourceManagerStringCreator.getPasswordSize(),
                                resourceManagerStringCreator.getKeyStartSymbol(),
                                resourceManagerStringCreator.getKeyEndSymbol(),
                                resourceManagerStringCreator.getPasswordStartSymbol(),
                                resourceManagerStringCreator.getPasswordEndSymbol());
    database = new StorageMySQL<QuerySet, LoggerDB>;
}

void TestDatabaseUtils::TearDown() {
    delete creator;
    delete database;
    delete logger;
    delete querySet;
    delete resourceManagerDatabase;
}

TEST_F(TestResourceManagerDatabase, tryToConnect) {
    StorageMySQL<QuerySet, LoggerDB> database;
    EXPECT_EQ(database.connect(resourceManagerDatabaseERROR->getHost(),
                                    resourceManagerDatabaseERROR->getUser(),
                                    resourceManagerDatabaseERROR->getPassword(),
                                    resourceManagerDatabaseERROR->getDatabase(),
                                    logger
                                   ), EXIT_FAILURE);
    EXPECT_EQ(database.connect(resourceManagerDatabaseSUCCESS->getHost(),
                                    resourceManagerDatabaseSUCCESS->getUser(),
                                    resourceManagerDatabaseSUCCESS->getPassword(),
                                    resourceManagerDatabaseSUCCESS->getDatabase(),
                                    logger
                                   ), EXIT_SUCCESS);
}

TEST_F(TestDatabaseUtils, tryToSaveDataWhenConnected) {
    map<string, string> result;
    EXPECT_EQ(database->connect(resourceManagerDatabase->getHost(),
                      resourceManagerDatabase->getUser(),
                      resourceManagerDatabase->getPassword(),
                      resourceManagerDatabase->getDatabase(),
                      logger
                      ), EXIT_SUCCESS);
    string key;
    string password = creator->createPassword();
    string deletionDate = StringCreator::createDeletionDate(amountOfDays);
    do {
         key = creator->createKey();
         database->getData(key, querySet, logger);
         if (querySet) {
            result = querySet->GetQuerySetRow();
        }
    } while (result["Key"] == key);
    EXPECT_EQ(database->saveData(key, password, deletionDate, logger), EXIT_SUCCESS);
    EXPECT_EQ(database->saveData(key, password, deletionDate, logger), EXIT_FAILURE);
}

TEST_F(TestDatabaseUtils, tryToSaveDataWhenNotConnected) {
    map<string, string> result;
    EXPECT_EQ(database->connect(resourceManagerDatabase->getHost(),
                                resourceManagerDatabase->getUser(),
                                resourceManagerDatabase->getPassword(),
                                "",
                                logger
    ), EXIT_FAILURE);
    string key;
    string password = creator->createPassword();
    string deletionDate = StringCreator::createDeletionDate(amountOfDays);
    do {
        key = creator->createKey();
        database->getData(key, querySet, logger);
        if (querySet) {
            result = querySet->GetQuerySetRow();
        }
    } while (result["Key"] == key);
    EXPECT_EQ(database->saveData(key, password, deletionDate, logger), EXIT_FAILURE);
}

TEST_F(TestDatabaseUtils, tryToGetData) {
    map<string, string> result;
    EXPECT_EQ(database->connect(resourceManagerDatabase->getHost(),
                                resourceManagerDatabase->getUser(),
                                resourceManagerDatabase->getPassword(),
                                resourceManagerDatabase->getDatabase(),
                                logger
    ), EXIT_SUCCESS);
    string key;
    string password = creator->createPassword();
    string deletionDate = StringCreator::createDeletionDate(amountOfDays);
    do {
        key = creator->createKey();
        database->getData(key, querySet, logger);
        if (querySet) {
            result = querySet->GetQuerySetRow();
        }
    } while (result["Key"] == key);
    EXPECT_EQ(result.empty(), NULL);
    EXPECT_EQ(database->saveData(key, password, deletionDate, logger), EXIT_SUCCESS);
    database->getData(key, querySet, logger);
    if (querySet) {
        result = querySet->GetQuerySetRow();
    }
    EXPECT_EQ(result["Key"], key);
}

