#ifndef TLCONSOLEAPPLICATION_NETWORK_H
#define TLCONSOLEAPPLICATION_NETWORK_H

const size_t BUF_SIZE = 8192;
const std::string HOST = "127.0.0.1";
const size_t PORT = 8000;
const std::string OK_RESPONSE = "200 OK";
const std::string REQUEST_HEADER_END = "\r\n\r\n";
const std::string REQUEST_NEW_LINE = "\r\n";
const size_t TRANSFER_AT_LEAST_NUMBER = 1;
const std::string TIMELOCKER_BOUNDARY = "236756838103946005692102";
const std::string POST_REQUEST_ENDING = "\r\n--236756838103946005692102--\r\n";
const size_t POST_REQUEST_BODY_SIZE = 146;
const std::string POST_ADDRESS = "/api/post/";
const std::string GET_ADDRESS = "/api/get/";

using std::cin;
using std::cout;

class HeaderCreator {
public:
    HeaderCreator(AbstractModel *abstractModel) : model(abstractModel) {}

    void makeGETRequestOnDownload(std::string &header);

    void makePOSTRequestOnUpload(std::string &header);

private:

    AbstractModel *model;
};

class HeaderHandler {
public:
    HeaderHandler(AbstractModel *abstractModel, std::string &headers_) : model(abstractModel), headers(headers_) {}

    std::string pickFileName();

    size_t pickFileLength();

    std::string pickFileKey();

    std::string pickServerResponse();

private:
    AbstractModel *model;
    std::string &headers;
};

class AbstractNetworkClient {
public:
    virtual void manageConnection() = 0;

    virtual ~AbstractNetworkClient() = default;

private:

    virtual void cleanUp() = 0;
};

#endif
