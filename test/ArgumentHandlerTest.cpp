#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "consoleApplication.h"

class ArgumentHandlerTest : public ::testing::Test {
public:
    std::ifstream input;
    int argc;
    char **argv;
protected:
    void SetUp() {
        argc = 0;
        argv = nullptr;
    }
    void TearDown() {}
};

TEST_F(ArgumentHandlerTest, HandlesDownloadArgument) {
    input.open(DOWNLOAD_ARGUMENT_TEST);
    input >> argc;
    argv = new char *[argc];

    for (int i = 0; i < argc; i++) {
        argv[i] = new char[BUFF_SIZE];
        input >> argv[i];
    }

    ArgumentHandler *argumentHandler = new ArgumentHandler(argc, argv);
    EXPECT_TRUE(argumentHandler->setEventID());
    EXPECT_EQ(argumentHandler->getEventID(), DOWNLOAD_EVENT);

    delete[] argv;
    delete argumentHandler;
}

TEST_F(ArgumentHandlerTest, HandlesUploadArgument) {
    input.open(UPLOAD_ARGUMENT_TEST);
    input >> argc;
    argv = new char *[argc];

    for (int i = 0; i < argc; i++) {
        argv[i] = new char[BUFF_SIZE];
        input >> argv[i];
    }

    ArgumentHandler *argumentHandler = new ArgumentHandler(argc, argv);
    EXPECT_TRUE(argumentHandler->setEventID());
    EXPECT_EQ(argumentHandler->getEventID(), UPLOAD_EVENT);

    delete[] argv;
    delete argumentHandler;
}

TEST_F(ArgumentHandlerTest, HandlesInvalidCountOfArguments) {
    input.open(INVALID_COUNT_OF_ARGUMENTS_TEST);
    input >> argc;
    argv = new char *[argc];

    for (int i = 0; i < argc; i++) {
        argv[i] = new char[BUFF_SIZE];
        input >> argv[i];
    }

    ArgumentHandler *argumentHandler = new ArgumentHandler(argc, argv);
    EXPECT_FALSE(argumentHandler->setEventID());

    delete[] argv;
    delete argumentHandler;
}

TEST_F(ArgumentHandlerTest, HandlesInvalidArgument) {
    input.open(INVALID_COUNT_OF_ARGUMENTS_TEST);
    input >> argc;
    argv = new char *[argc];

    for (int i = 0; i < argc; i++) {
        argv[i] = new char[BUFF_SIZE];
        input >> argv[i];
    }

    ArgumentHandler *argumentHandler = new ArgumentHandler(argc, argv);
    EXPECT_FALSE(argumentHandler->setEventID());

    delete[] argv;
    delete argumentHandler;
}

TEST_F(ArgumentHandlerTest, HandlesNoArguments) {
    input.open(NO_ARGUMENTS_TEST);
    input >> argc;
    argv = new char *[argc];

    for (int i = 0; i < argc; i++) {
        argv[i] = new char[BUFF_SIZE];
        input >> argv[i];
    }

    ArgumentHandler *argumentHandler = new ArgumentHandler(argc, argv);
    EXPECT_FALSE(argumentHandler->setEventID());

    delete[] argv;
    delete argumentHandler;
}
