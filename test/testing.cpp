#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <Web_Site.h>
#include <Controller.hpp>
#include <storageMYSQL.hpp>
#include "Logger.h"
#include "resourceManagerStringCreator.h"
#include "resourceManagerDatabase.h"


using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;

class MockDatabase{
public:
    MOCK_METHOD3(saveData,int(std::string const& key,std::string const& pass,std::string const &date));
    MOCK_METHOD2(getData,int(std::string const & key,QuerySet*&));
};


int Mock_get_function(const std::string& key,QuerySet*& querySet){
    querySet->Insert("Key", key, true);
    querySet->Insert("Password", "example");
    querySet->Insert("DeletionDate", "example");
    return EXIT_SUCCESS;
}

int Mock_validate_function(const std::string& key, QuerySet*& querySet){
    querySet->Insert("Key", "", true);
    querySet->Insert("Password", "example");
    querySet->Insert("DeletionDate", "example");
    return EXIT_SUCCESS;
}

int Set_null_function(const std::string& key,QuerySet*& querySet){
    querySet = nullptr;
    return EXIT_SUCCESS;
}


class TestController : public ::testing::Test{
protected:
    void SetUp(){
        ResourceManagerStringCreator resourceManagerStringCreator(PATH_TO_STRING_CREATOR);
        resourceManagerStringCreator.parseFile();
        querySet = new QuerySet;
        auto* creator = new StringCreator(resourceManagerStringCreator.getKeySize(),
                                          resourceManagerStringCreator.getPasswordSize(),
                                          resourceManagerStringCreator.getKeyStartSymbol(),
                                          resourceManagerStringCreator.getKeyEndSymbol(),
                                          resourceManagerStringCreator.getPasswordStartSymbol(),
                                          resourceManagerStringCreator.getPasswordEndSymbol());
        logger = new Logger("log.txt");
        view = new ViewController<MockDatabase>(&database,logger,creator);
    }
    void TearDown(){
        delete view;
        delete logger;
        delete querySet;
    }
    MockDatabase database;
    ViewController<MockDatabase>* view;
    QuerySet* querySet;
    Logger* logger;
};




TEST_F(TestController,GET_DATA_OK){
    std::string exampleKey = "ex";
    std::string examplePass = "example";
    std::map<std::string,std::string> res;
    res.insert(std::pair<std::string,std::string>(PASSMAP,examplePass));
    EXPECT_CALL(database,getData(_,_)).WillOnce(Invoke(Mock_get_function));
    ASSERT_EQ(SUCCESS,view->GetData(exampleKey,examplePass));
}


TEST_F(TestController,GET_DATA_FAIL){
    std::string exampleKey = "ex";
    std::string examplePass = "example";
    EXPECT_CALL(database,getData(_,_)).Times(1).WillOnce(Return(0));
    ASSERT_EQ(FAIL,view->GetData(exampleKey,examplePass));
}


TEST_F(TestController,GET_DATA_FAIL2){
    std::string exampleKey;
    std::string examplePass;
    ASSERT_EQ(FAIL,view->GetData(exampleKey,examplePass));
}

TEST_F(TestController,GET_DATA_FAIL3){
    std::string exampleKey = "ex";
    std::string examplePass = "example";
    std::map<std::string,std::string> res;
    res.insert(std::pair<std::string,std::string>(PASSMAP,examplePass));
    EXPECT_CALL(database,getData(_,_)).Times(1).WillOnce(Invoke(Set_null_function));
    ASSERT_EQ(FAIL,view->GetData(exampleKey,examplePass));
}

TEST_F(TestController,GET_DATA_FAIL4){
    std::string exampleKey = "ex";
    std::string examplePass = "example";
    std::map<std::string,std::string> res;
    res.insert(std::pair<std::string,std::string>(PASSMAP,examplePass));
    EXPECT_CALL(database,getData(_,_)).Times(1).WillOnce(Return(1));
    ASSERT_EQ(FAIL,view->GetData(exampleKey,examplePass));
}


TEST_F(TestController,VALIDATE_DATA_FAIL){
    std::string examplePass = "example";
    std::string exampleKey = "ex";
    EXPECT_CALL(database,getData(_,_)).Times(1).WillOnce(Invoke(Set_null_function));
    EXPECT_EQ(FAIL,view->ValidateData(exampleKey,examplePass));
}

TEST_F(TestController,VALIDATE_DATA_FAIL2){
    std::string examplePass;
    std::string exampleKey = "ex";
    EXPECT_CALL(database,getData(_,_)).Times(1).WillOnce(Invoke(Set_null_function));
    EXPECT_EQ(FAIL,view->ValidateData(exampleKey,examplePass));
}

TEST_F(TestController,VALIDATE_DATA_OK){
    std::string examplePass = "example";
    std::string exampleKey = "ex";
    EXPECT_CALL(database,getData(_,_)).WillRepeatedly(Invoke(Mock_validate_function));
    EXPECT_EQ(SUCCESS,view->ValidateData(exampleKey,examplePass));
}


TEST_F(TestController,POST_DATA_OK){
    std::string examplePass = "asd";
    int daysEx = 5;
    EXPECT_CALL(database,getData(_,_)).Times(1).WillOnce(Invoke(Mock_validate_function));
    EXPECT_CALL(database,saveData(_,_,_)).Times(1).WillOnce(Return(SUCCESSFUL));
    EXPECT_NE("",view->PostData(examplePass,daysEx));
}


TEST_F(TestController,POST_DATA_FAIL){
    std::string examplePass = "asd";
    int daysEx = 5;
    EXPECT_CALL(database,getData(_,_)).Times(1).WillOnce(Invoke(Set_null_function));
    EXPECT_EQ("",view->PostData(examplePass,daysEx));
}

TEST_F(TestController,POST_DATA_FAIL2){
    std::string examplePass = "example";
    int daysEx = 5;
    EXPECT_CALL(database,getData(_,_)).WillRepeatedly(Invoke(Mock_validate_function));
    EXPECT_CALL(database,saveData(_,_,_)).WillOnce(Return(EXIT_FAILURE));
    EXPECT_EQ("",view->PostData(examplePass,daysEx));
}


