#include "gtest/gtest.h"
#include "View.h"
#include <fstream>


class TestModel : public ::testing::Test {
public:
    void SetUp() override {
        model = new Model{};
    }

    void TearDown() override {
        delete model;
    }
    AbstractModel* model;
};

TEST_F(TestModel, HandlesEditigFilePassword) {

    std::string password = "ladiesman217";

    model->setFilePassword(password);
    EXPECT_EQ(password, model->getFilePassword());
}

TEST_F(TestModel, HandlesEditigFilePath) {

    std::string filePath = "/path/to/something";

    model->setFilePath(filePath);
    EXPECT_EQ(filePath, model->getFilePath());
}

TEST_F(TestModel, HandlesEditigFileLifetime) {

    std::string fileLifetime = "7";

    model->setFileLifetime(fileLifetime);
    EXPECT_EQ(fileLifetime, model->getFileLifetime());
}

TEST_F(TestModel, HandlesEditigAppMode) {

    std::string appMode = "u";

    model->setApplicationMode(appMode);
    EXPECT_EQ(appMode, model->getApplicationMode());
}

TEST_F(TestModel, HandlesEditigExitMessage) {

    std::string exitMessage = "OK";

    model->setExitMessage(exitMessage);
    EXPECT_EQ(exitMessage, model->getExitMessage());
}

TEST_F(TestModel, HandlesEditigFileKey) {

    std::string fileKey = "asdfasdfasdfasdfasdfasdfadsfasdf";

    model->setFileKey(fileKey);
    EXPECT_EQ(fileKey, model->getFileKey());
}
