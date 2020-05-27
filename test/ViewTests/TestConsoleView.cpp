#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "View.h"
#include <fstream>

class MockApplicationPresenter : public AbstractApplicationPresenter {
public:
    MockApplicationPresenter() = default;

    MOCK_METHOD0(start, int());
    MOCK_METHOD0(setApplicationMode, int());
    MOCK_METHOD0(setDownloadInfo, int());
    MOCK_METHOD1(setEnteredData, int(std::string&));
    MOCK_METHOD0(setUploadInfo, int());

};

class TestConsoleView : public ::testing::Test {
public:
    void SetUp() override {
        testAppPresenter = new MockApplicationPresenter();
        setKeyPage = new ConsoleViewSetKeyPage{testAppPresenter, input, output};
        downloadMessagePage = new ConsoleViewDownloadFileMessagePage{testAppPresenter, input, output};
        setPasswordPage = new ConsoleViewSetPasswordPage{testAppPresenter, input, output};
        setFilePathPage = new ConsoleViewSetFilePathPage{testAppPresenter, input, output};
        setUserPasswordPage = new ConsoleViewSetEnteredUsersPasswordPage{testAppPresenter, input, output};
        setFileLifetimePage = new ConsoleViewSetFileLifetimePage{testAppPresenter, input, output};
        uploadMessagePage = new ConsoleViewUploadFileMessagePage{testAppPresenter, input, output};
        setApplicationModePage = new ConsoleViewSetApplicationModePage{testAppPresenter, input, output};
        startPage = new ConsoleViewStartPage{testAppPresenter, input, output};
        exitMessagePage = new ConsoleViewExitMessagePage{output};
    }
    void TearDown() override {
        delete testAppPresenter;
        delete downloadMessagePage;
        delete setKeyPage;
        delete setPasswordPage;
        delete setFilePathPage;
        delete setUserPasswordPage;
        delete setFileLifetimePage;
        delete uploadMessagePage;
        delete setApplicationModePage;
        delete startPage;
        delete exitMessagePage;
    }

    ConsoleViewDownloadFileMessagePage* downloadMessagePage;
    ConsoleViewSetKeyPage *setKeyPage;
    ConsoleViewSetPasswordPage *setPasswordPage;
    ConsoleViewUploadFileMessagePage* uploadMessagePage;
    ConsoleViewSetFilePathPage *setFilePathPage;
    ConsoleViewSetEnteredUsersPasswordPage *setUserPasswordPage;
    ConsoleViewSetFileLifetimePage *setFileLifetimePage;
    ConsoleViewSetApplicationModePage* setApplicationModePage;
    ConsoleViewStartPage *startPage;
    ConsoleViewExitMessagePage *exitMessagePage;

    std::ifstream input;
    std::ofstream output;
    MockApplicationPresenter *testAppPresenter;
};

TEST_F(TestConsoleView, HandlesTheOnlyDownloadMessageCase) {
    output.open(OUTPUT);

    EXPECT_EQ(downloadMessagePage->printPage(), SUCCESS);

    output.close();
}

TEST_F(TestConsoleView, HandlesEnteringCorrectFileKey) {
    std::string correctKey;
    input.open(VALID_FILE_KEY);
    output.open(OUTPUT);

    input >> correctKey;
    input.clear();
    input.seekg(0);

    EXPECT_CALL(*testAppPresenter, setEnteredData(correctKey)).WillOnce(::testing::Return(SUCCESS));

    EXPECT_EQ(setKeyPage->printPage(), SUCCESS);

    input.close();
    output.close();
}

TEST_F(TestConsoleView, HandlesEnteringIncorrectFileKey) {
    std::string correctKey;
    input.open(INVALID_FILE_KEY);
    output.open(OUTPUT);

    input >> correctKey; // Ключ с неподдерживаемыми символами
    input >> correctKey; // Ключ некоректной длины

    input >> correctKey; // Корректный ключ, для остановки чтения

    input.clear();
    input.seekg(0, std::ios_base::beg);

    EXPECT_CALL(*testAppPresenter, setEnteredData(correctKey)).WillOnce(::testing::Return(SUCCESS));

    EXPECT_EQ(setKeyPage->printPage(), SUCCESS);

    input.close();
    output.close();
}

TEST_F(TestConsoleView, HandlesEnteringCorrectPassword) {
    std::string correctPassword;
    input.open(VALID_PASSWORD);
    output.open(OUTPUT);

    input >> correctPassword; // Корректный пароль

    input.clear();
    input.seekg(0, std::ios_base::beg);

    EXPECT_CALL(*testAppPresenter, setEnteredData(correctPassword)).WillOnce(::testing::Return(SUCCESS));

    EXPECT_EQ(setPasswordPage->printPage(), SUCCESS);

    input.close();
    output.close();
}

TEST_F(TestConsoleView, HandlesEnteringIncorrectFilePassword) {
    std::string correctPassword;
    input.open(INVALID_PASSWORD);
    output.open(OUTPUT);

    input >> correctPassword; // Слишком короткий пароль
    input >> correctPassword; // Слишком длинный пароль

    input >> correctPassword; // Верный пароль, для остановки чтения

    input.clear();
    input.seekg(0, std::ios_base::beg);

    EXPECT_CALL(*testAppPresenter, setEnteredData(correctPassword)).WillOnce(::testing::Return(SUCCESS));

    EXPECT_EQ(setPasswordPage->printPage(), SUCCESS);

    input.close();
    output.close();
}

TEST_F(TestConsoleView, HandlesEnteringCorrectFilePath) {
    std::string correctFilePath;
    output.open(VALID_FILE_PATH);
    output << OUTPUT;
    output.close();

    input.open(VALID_FILE_PATH);
    input >> correctFilePath; // Корректный путь
    input.clear();
    input.seekg(0, std::ios_base::beg);

    EXPECT_CALL(*testAppPresenter, setEnteredData(correctFilePath)).WillOnce(::testing::Return(SUCCESS));

    EXPECT_EQ(setFilePathPage->printPage(), SUCCESS);

    input.close();
    output.close();
}

TEST_F(TestConsoleView, HandlesEnteringIncorrectFilePath) {
    std::string correctFilePath;
    output.open(INVALID_FILE_PATH);
    output << INVALID_FILE_PATH << 'a' << std::endl << OUTPUT;
    output.close();

    input.open(INVALID_FILE_PATH);
    input >> correctFilePath; // Некорректный путь
    input >> correctFilePath; // Корректный путь
    input.clear();
    input.seekg(0, std::ios_base::beg);

    EXPECT_CALL(*testAppPresenter, setEnteredData(correctFilePath)).WillOnce(::testing::Return(SUCCESS));

    EXPECT_EQ(setFilePathPage->printPage(), SUCCESS);

    input.close();
    output.close();
}

TEST_F(TestConsoleView, HandlesEnteringCorrectUserPasswordPair) {
    std::string correctPassword;
    input.open(INVALID_PASSWORD_PAIR);
    output.open(OUTPUT);

    input >> correctPassword; // Неверная пара паролей
    input >> correctPassword; // Неверная пара паролей

    input >> correctPassword; // Неверная пара паролей
    input >> correctPassword; // Неверная пара паролей

    input >> correctPassword; // Верный пароль

    input.clear();
    input.seekg(0, std::ios_base::beg);

    EXPECT_CALL(*testAppPresenter, setEnteredData(correctPassword)).WillOnce(::testing::Return(SUCCESS));

    EXPECT_EQ(setUserPasswordPage->printPage(), SUCCESS);

    input.close();
    output.close();
}

TEST_F(TestConsoleView, HandlesEnteringIncorrectUserPasswordPair) {
    std::string correctPassword;
    input.open(VALID_PASSWORD_PAIR);
    output.open(OUTPUT);

    input >> correctPassword; // Корректный пароль

    input.clear();
    input.seekg(0, std::ios_base::beg);

    EXPECT_CALL(*testAppPresenter, setEnteredData(correctPassword)).WillOnce(::testing::Return(SUCCESS));

    EXPECT_EQ(setUserPasswordPage->printPage(), SUCCESS);

    input.close();
    output.close();
}

TEST_F(TestConsoleView, HandlesEnteringCorrectFileLifetime) {
    std::string correctFileLifetime;
    input.open(VALID_FILE_LIFETIME);
    output.open(OUTPUT);

    input >> correctFileLifetime; // Корректный пароль

    input.clear();
    input.seekg(0, std::ios_base::beg);

    EXPECT_CALL(*testAppPresenter, setEnteredData(correctFileLifetime)).WillOnce(::testing::Return(SUCCESS));

    EXPECT_EQ(setFileLifetimePage->printPage(), SUCCESS);

    input.close();
    output.close();
}

TEST_F(TestConsoleView, HandlesEnteringIncorrectFileLifetime) {
    std::string correctFileLifetime;
    input.open(INVALID_FILE_LIFETIME);
    output.open(OUTPUT);

    input >> correctFileLifetime; // Время хранения не в заданных границах
    input >> correctFileLifetime; // Значение не соответствует времени в днях

    input >> correctFileLifetime; // Верное время хранения

    input.clear();
    input.seekg(0, std::ios_base::beg);

    EXPECT_CALL(*testAppPresenter, setEnteredData(correctFileLifetime)).WillOnce(::testing::Return(SUCCESS));

    EXPECT_EQ(setFileLifetimePage->printPage(), SUCCESS);

    input.close();
    output.close();
}

TEST_F(TestConsoleView, HandlesTheOnlyUploadMessageCase) {
    output.open(OUTPUT);

    EXPECT_EQ(uploadMessagePage->printPage(), SUCCESS);

    output.close();
}

TEST_F(TestConsoleView, HandlesEnteringCorrectAppMode) {
    input.open(VALID_APP_MODE);
    output.open(OUTPUT);

    std::string mode;
    mode.push_back(DOWNLOAD_MODE);
    EXPECT_CALL(*testAppPresenter, setEnteredData(mode)).WillOnce(::testing::Return(SUCCESS));
    EXPECT_EQ(setApplicationModePage->printPage(), SUCCESS);

    mode.pop_back();
    mode.push_back(UPLOAD_MODE);
    EXPECT_CALL(*testAppPresenter, setEnteredData(mode)).WillOnce(::testing::Return(SUCCESS));
    EXPECT_EQ(setApplicationModePage->printPage(), SUCCESS);

    input.close();
    output.close();
}

TEST_F(TestConsoleView, HandlesEnteringIncorrectAppMode) {
    input.open(INVALID_APP_MODE);
    output.open(OUTPUT);

    // Прочтет два неверных режима приложения и выйдет из цикла режиме скачивания

    std::string mode;
    mode.push_back(DOWNLOAD_MODE);
    EXPECT_CALL(*testAppPresenter, setEnteredData(mode)).WillOnce(::testing::Return(SUCCESS));
    EXPECT_EQ(setApplicationModePage->printPage(), SUCCESS);

    input.close();
    output.close();
}

TEST_F(TestConsoleView, HandlesTheOnlyExitMessageCase) {
    output.open(OUTPUT);

    EXPECT_EQ(startPage->printPage(), SUCCESS);

    output.close();
}

TEST_F(TestConsoleView, HandlesTheOnlyStartPageCase) {
    output.open(OUTPUT);

    EXPECT_EQ(exitMessagePage->printInfo("OK"), SUCCESS);

    output.close();
}
