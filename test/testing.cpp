#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include "Controller.hpp"
#include "stringCreator.h"
#include "Web_Site.h"
#include <map>


using ::testing::Return;
using ::testing::_;

class MockDatabase{
public:
    MOCK_METHOD3(saveData,int(std::string const &date,std::string const& key,std::string const& pass));
    MOCK_METHOD1(getData,std::map<std::string,std::string>(std::string const & key));
};


class TestController : public ::testing::Test{
protected:
    void SetUp(){
        view = new ViewController<MockDatabase>(&database);
    }
    void TearDown(){
        delete view;
    }
    MockDatabase database;
    ViewController<MockDatabase>* view;
};




TEST_F(TestController,test1){
    std::string exampleKey = "ex";
    std::string examplePass = "eex";
    std::map<std::string,std::string> res;
    res.insert(std::pair<std::string,std::string>(PASSMAP,examplePass));
    EXPECT_CALL(database,getData(exampleKey)).Times(1).WillOnce(Return(res));
    ASSERT_EQ(SUCCESS,view->GetData(exampleKey,examplePass));
}


TEST_F(TestController,test2){
    std::string exampleKey = "ex";
    std::string examplePass = "eex";
    std::map<std::string,std::string> res;
    EXPECT_CALL(database,getData(exampleKey)).Times(1).WillOnce(Return(res));
    ASSERT_EQ(FAIL,view->GetData(exampleKey,examplePass));
}

TEST_F(TestController,test3){
    ASSERT_EQ(FAIL,view->GetData("",""));
}

TEST_F(TestController,test4){
    std::string examplePass = "";
    std::string exampleKey = "ex";
    EXPECT_EQ(SUCCESS,view->ValidateData(exampleKey,examplePass));
}


TEST_F(TestController,test5){
    std::string examplePass = "asd";
    int daysEx = 5;
    std::string a = "";
    EXPECT_CALL(database,saveData(_,_,_)).Times(1).WillOnce(Return(EXIT_SUCCESS));
    EXPECT_NE(a,view->PostData(examplePass,daysEx));
}


TEST_F(TestController,test6){
    std::string examplePass = "asd";
    int daysEx = 5;
    std::string a = "";
    EXPECT_CALL(database,saveData(_,_,_)).Times(1).WillOnce(Return(EXIT_FAILURE));
    EXPECT_EQ(a,view->PostData(examplePass,daysEx));
}


