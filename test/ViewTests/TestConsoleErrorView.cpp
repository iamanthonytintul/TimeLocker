#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "View.h"
#include <fstream>


class TestConsoleErrorView : public ::testing::Test {
public:
    void SetUp() override {
        output.open(OUTPUT);
        errorView = new ConsoleErrorView{};
    }

    void TearDown() override {
        output.close();
        delete errorView;
    }
    ConsoleErrorView* errorView;
    std::ofstream output;
};

TEST_F(TestConsoleErrorView, HandlesPasswordErrors) {
    //Вывод сообщения в output и успешный возврат

    EXPECT_EQ(errorView->filePasswordErrorPrint(output, NO_DATA_WAS_READ), SUCCESS);
    EXPECT_EQ(errorView->filePasswordErrorPrint(output, TOO_SHORT_PASSWORD), SUCCESS);
    EXPECT_EQ(errorView->filePasswordErrorPrint(output, TOO_LONG_PASSWORD), SUCCESS);
    EXPECT_EQ(errorView->filePasswordErrorPrint(output, INIT_VALUE), SUCCESS);

}
TEST_F(TestConsoleErrorView, HandlesFilePathErrors) {
    //Вывод сообщения в output и успешный возврат

    EXPECT_EQ(errorView->filePathErrorPrint(output, NO_DATA_WAS_READ), SUCCESS);
    EXPECT_EQ(errorView->filePathErrorPrint(output, NO_SUCH_FILE_IN_DIRECTORY), SUCCESS);
    EXPECT_EQ(errorView->filePathErrorPrint(output, INIT_VALUE), SUCCESS);

}
TEST_F(TestConsoleErrorView, HandlesFileLifetimeErrors) {
    //Вывод сообщения в output и успешный возврат

    EXPECT_EQ(errorView->fileLifeTimeErrorPrint(output, NO_DATA_WAS_READ), SUCCESS);
    EXPECT_EQ(errorView->fileLifeTimeErrorPrint(output, OUT_OF_BORDER_LIFETIME), SUCCESS);
    EXPECT_EQ(errorView->fileLifeTimeErrorPrint(output, NOT_LIFETIME_VALUE), SUCCESS);
    EXPECT_EQ(errorView->fileLifeTimeErrorPrint(output, INIT_VALUE), SUCCESS);

}
TEST_F(TestConsoleErrorView, HandlesAppModeErrors) {
    //Вывод сообщения в output и успешный возврат

    EXPECT_EQ(errorView->applicationModeErrorPrint(output, NO_DATA_WAS_READ), SUCCESS);
    EXPECT_EQ(errorView->applicationModeErrorPrint(output, OUT_OF_BORDER_MODE), SUCCESS);
    EXPECT_EQ(errorView->applicationModeErrorPrint(output, NOT_MODE_VALUE), SUCCESS);
    EXPECT_EQ(errorView->applicationModeErrorPrint(output, INIT_VALUE), SUCCESS);

}
TEST_F(TestConsoleErrorView, HandlesFileKeyErrors) {
    //Вывод сообщения в output и успешный возврат

    EXPECT_EQ(errorView->fileKeyErrorPrint(output, NO_DATA_WAS_READ), SUCCESS);
    EXPECT_EQ(errorView->fileKeyErrorPrint(output, OUT_SIZE_OF_KEY), SUCCESS);
    EXPECT_EQ(errorView->fileKeyErrorPrint(output, NOT_KEY_VALUE), SUCCESS);
    EXPECT_EQ(errorView->fileKeyErrorPrint(output, INIT_VALUE), SUCCESS);

}