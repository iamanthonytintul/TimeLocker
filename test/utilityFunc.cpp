#include <iostream>
#include "gtest/gtest.h"
#include "Web_Site.h"

TEST(fileExists,ok){
    std::string path = "log.txt";
    bool res = fileExists(PATH_TO_FILE_LOGS + path);
    EXPECT_EQ(res,true);
}


TEST(fileExists,not_ok){
    std::string path = "non_existing_file";
    bool res = fileExists(PATH_TO_FILE_LOGS + path);
    EXPECT_EQ(res,false);
}

TEST(delimeterFunc,ok){
    std::string req = "key:password";
    std::string key;
    std::string pass;
    EXPECT_EQ(SUCCESS,delimeterFunc(req,key,pass));
}

TEST(delimeterFunc,not_ok){
    std::string req = "keypassword";
    std::string key;
    std::string pass;
    EXPECT_EQ(FAIL,delimeterFunc(req,key,pass));
}

TEST(toInt,ok){
    std::string req = "123";
    EXPECT_EQ(123,toInt(req));
}

TEST(toInt,not_ok){
    std::string req = "asd123";
    EXPECT_EQ(DEFAULT_TIME,toInt(req));
}