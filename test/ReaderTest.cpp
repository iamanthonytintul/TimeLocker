#include "gtest/gtest.h"
#include "consoleApplication.h"

TEST(ReaderTest, HandlesValidPasswordRead) {
    IReader<char *> *passwordReader = new PasswordReader<char *>();
    FILE *testRead = fopen(VALID_PASSWORD_TEST, "r");
    EXPECT_NE(testRead, nullptr);

    char* testPassword = new char[BUFF_SIZE];
    int errorFlag = passwordReader->read(testRead, &testPassword, BUFF_SIZE);
    EXPECT_EQ(errorFlag, SUCCESS);

    delete passwordReader;
    fclose(testRead);
    delete [] testPassword;
}

TEST(ReaderTest, HandlesInvalidPasswordRead) {
    IReader<char *> *passwordReader = new PasswordReader<char *>();
    FILE *testRead = fopen(VALID_PASSWORD_TEST, "r");
    EXPECT_NE(testRead, nullptr);

    char* testPassword = new char[BUFF_SIZE];
    int errorFlag = passwordReader->read(testRead, &testPassword, BUFF_SIZE);
    EXPECT_EQ(errorFlag, TOO_LONG_PASSWORD);

    delete passwordReader;
    fclose(testRead);
    delete [] testPassword;
}

TEST(ReaderTest, HandlesValidFilePathReader) {
    IReader<char*> *filePathReader = new FilePathReader<char*>();

    FILE *testRead = fopen(VALID_PASSWORD_TEST, "r");
    EXPECT_NE(testRead, nullptr);

    char* testFilePath = new char[BUFF_SIZE];
    int errorFlag = filePathReader->read(testRead, &testFilePath, BUFF_SIZE);
    EXPECT_EQ(errorFlag, SUCCESS);

    delete filePathReader;
    fclose(testRead);
    delete [] testFilePath;
}

TEST(ReaderTest, HandlesInvalidFilePathReader) {
    IReader<char*> *filePathReader = new FilePathReader<char*>();

    FILE* testRead = fopen(INVALID_FILE_PATH_TEST, "r");
    EXPECT_NE(testRead, nullptr);

    char* testFilePath = new char[BUFF_SIZE];
    int errorFlag = filePathReader->read(testRead, &testFilePath, BUFF_SIZE);
    EXPECT_EQ(errorFlag, INVALID_PATH);

    delete filePathReader;
    fclose(testRead);
    delete [] testFilePath;
}

TEST(ReaderTest, HandlesNoSuchFile) {
    IReader<char*> *filePathReader = new FilePathReader<char*>();

    FILE* testRead = fopen(INVALID_FILE_PATH_TEST, "r");
    EXPECT_NE(testRead, nullptr);

    char* testFilePath = new char[BUFF_SIZE];
    int errorFlag = filePathReader->read(testRead, &testFilePath, BUFF_SIZE);
    EXPECT_EQ(errorFlag, NO_SUCH_FILE);

    delete filePathReader;
    fclose(testRead);
    delete [] testFilePath;
}
