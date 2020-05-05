#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <service.h>
#include "Controller.hpp"
#include "NameCreator.h"
#include "Web_Site.h"



using ::testing::Return;

class MockDatabase{
public:
    MOCK_METHOD3(insert_data,bool(std::string const &url,std::string const& key,std::string const& pass));
    MOCK_METHOD2(get_data,std::string(std::string const & key, std::string const& pass));
};



TEST(Controller,getData_ok){
    MockDatabase database;
    AbstractController* view = new ViewController<MockDatabase>(&database);
    std::string keyTest = "ex_key";
    std::string passTest = "ex_pass";
    char* pathTest = (char*)"ex_path";
    std::string DBresponseTest = "ex_response";
    EXPECT_CALL(database,get_data(keyTest,passTest)).Times(1).WillOnce(Return(DBresponseTest));
    char* key_res = view->GetData(keyTest,passTest);
    EXPECT_STREQ(pathTest,key_res);
    delete view;
}


TEST(Controller,getData_not_ok){
    MockDatabase database;
    AbstractController* view = new ViewController<MockDatabase>(&database);
    std::string keyTest = "ex_key";
    std::string passTest = "ex_pass";
    std::string pathTest = "ex_path";
    std::string DBresponseTest = "ex_false_response";
    EXPECT_CALL(database,get_data(keyTest,passTest)).Times(1).WillOnce(Return(DBresponseTest));
    char* key_res = view->GetData(keyTest,passTest);
    EXPECT_STREQ(NULL,key_res);
    delete view;
}


TEST(Controller,insertData_ok){
    MockDatabase database;
    AbstractController* view = new ViewController<MockDatabase>(&database);
    std::string keyTest = "ex_key";
    std::string passTest = "ex_pass";
    std::string UrlTest = "ex_url";
    EXPECT_CALL(database,insert_data(UrlTest,keyTest,passTest)).Times(1).WillOnce(Return(true));
    bool ans_test = view->PostData(UrlTest);
    EXPECT_TRUE(ans_test);
    delete view;
}


TEST(Controller,insertData_not_ok){
    MockDatabase database;
    AbstractController* view = new ViewController<MockDatabase>(&database);
    std::string keyTest = "ex_key";
    std::string passTest = "ex_pass";
    std::string UrlTest = "ex_url";
    EXPECT_CALL(database,insert_data(UrlTest,keyTest,passTest)).Times(1).WillOnce(Return(false));
    bool ans_test = view->PostData(UrlTest);
    EXPECT_FALSE(ans_test);
    delete view;
}

TEST(UniqueNameCreator,createKey_ok){
    UniqueNameMaker nameCreator;
    std::string key_ex1 = "key_ex";
    std::string key_ex2 = "key2_ex";
    char* ans1 = nameCreator.createKey(key_ex1);
    char* ans2 = nameCreator.createKey(key_ex2);
    EXPECT_NE(ans1,ans2);
}

TEST(UniqueNameMaker,createKey_not_ok){
    UniqueNameMaker nameCreator;
    std::string key_ex;
    char* ans = nameCreator.createKey(key_ex);
    EXPECT_EQ(NULL,ans);
}





