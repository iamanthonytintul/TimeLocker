#include <iostream>
#include <fcntl.h>
#include <fstream>
#include "gtest/gtest.h"
#include "consoleApplication.h"

TEST(DownloadManagerTest, HandlesValidDownload) {

    std::ifstream input;
    input.open(VALID_DOWNLOAD_TEST);
    char* testInput = new char[BUFF_SIZE];
    int fileDescriptor;
    fileDescriptor = open(VALID_DOWNLOAD_TEST, O_WRONLY);
    ServerDownload<char *> *serverDownload = new ServerDownload<char *>();

    EXPECT_STREQ(serverDownload->DownloadData(fileDescriptor), testInput);

    delete serverDownload;
    delete [] testInput;
    close(fileDescriptor);
}

TEST(DownloadManagerTest, HandlesInvalidDownload) {
    int fileDescriptor = -1;
    ServerDownload<char *> *serverDownload = new ServerDownload<char *>();

    EXPECT_EQ(serverDownload->DownloadData(fileDescriptor), nullptr);

    delete serverDownload;
}