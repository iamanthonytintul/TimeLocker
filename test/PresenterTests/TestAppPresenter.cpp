#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "View.h"
#include <fstream>

class MockNetworkClient : public AbstractNetworkClient {
public:
    MockNetworkClient() = default;

    MOCK_METHOD0(manageConnection, void());

private:
    MOCK_METHOD0(cleanUp, void());
};

class MockModel : public AbstractModel {
public:
    MockModel() = default;

    MOCK_METHOD1(setFilePath, void(const std::string &));

    MOCK_METHOD1(setFileKey, void(const std::string &));

    MOCK_METHOD1(setFileLifetime, void(const std::string &));

    MOCK_METHOD1(setApplicationMode, void(const std::string &));

    MOCK_METHOD1(setExitMessage, void(const std::string &));

    MOCK_METHOD1(setFilePassword, void(const std::string &));

    MOCK_METHOD0(getFilePassword, const std::string&());

    MOCK_METHOD0(getFilePath, const std::string&());

    MOCK_METHOD0(getFileKey, const std::string&());

    MOCK_METHOD0(getFileLifetime, const std::string&());

    MOCK_METHOD0(getApplicationMode, const std::string&());

    MOCK_METHOD0(getExitMessage, const std::string&());

};

class TestAppPresenter : public ::testing::Test {
public:
    void SetUp() override {
        testNetworkClient = new MockNetworkClient();
        testModel = new MockModel();
        testAppPresenter = new ApplicationPresenter{testModel, testNetworkClient, input, output};
    }

    void TearDown() override {
        delete testAppPresenter;
        delete testNetworkClient;
        delete testModel;
    }

    std::ifstream input;
    std::ofstream output;
    ApplicationPresenter *testAppPresenter;
    MockNetworkClient *testNetworkClient;
    MockModel *testModel;
};

TEST_F(TestAppPresenter, HandlesStandartDownloadScript) {
    input.open(DOWNLOAD_SCRIPT);
    output.open(OUTPUT);

    std::string appMode;
    std::string fileKey;
    std::string filePassword;
    const std::string message = "OK";

    input >> appMode >> fileKey >> filePassword;
    input.clear();
    input.seekg(0, std::ios_base::beg);

    EXPECT_CALL(*testNetworkClient, manageConnection()).Times(1);
    EXPECT_CALL(*testModel, setApplicationMode(appMode)).Times(1);
    EXPECT_CALL(*testModel, setFileKey(fileKey)).Times(1);
    EXPECT_CALL(*testModel, setFilePassword(filePassword)).Times(1);
    EXPECT_CALL(*testModel, getExitMessage()).WillOnce(::testing::ReturnRef(message));

    EXPECT_EQ(testAppPresenter->start(), SUCCESS);

    output.close();
    input.close();
}

TEST_F(TestAppPresenter, HandlesStandartUploadScript) {
    output.open(UPLOAD_SCRIPT);

    std::string appMode;
    appMode.push_back(UPLOAD_MODE);
    std::string filePath = UPLOAD_SCRIPT;
    std::string fileLifetime = std::to_string(MAX_FILE_LIFETIME_DAYS);
    std::string filePassword = "ladiesman217";
    const std::string message = "OK";

    output << appMode << std::endl << filePath << std::endl << fileLifetime << std::endl << filePassword << std::endl
           << filePassword << std::endl;
    output.close();

    input.open(UPLOAD_SCRIPT);
    output.open(OUTPUT);

    input.clear();
    input.seekg(0, std::ios_base::beg);

    EXPECT_CALL(*testNetworkClient, manageConnection()).Times(1);
    EXPECT_CALL(*testModel, setApplicationMode(appMode)).Times(1);
    EXPECT_CALL(*testModel, setFilePath(filePath)).Times(1);
    EXPECT_CALL(*testModel, setFileLifetime(fileLifetime)).Times(1);
    EXPECT_CALL(*testModel, setFilePassword(filePassword)).Times(1);
    EXPECT_CALL(*testModel, getExitMessage()).WillOnce(::testing::ReturnRef(message));

    EXPECT_EQ(testAppPresenter->start(), SUCCESS);

    output.close();
    input.close();
}