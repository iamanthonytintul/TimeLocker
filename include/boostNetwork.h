#ifndef TLCONSOLEAPPLICATION_BOOSTNETWORK_H
#define TLCONSOLEAPPLICATION_BOOSTNETWORK_H

#include <iostream>
#include <fstream>
#include <string>
#include <boost/asio.hpp>
#include <cstdlib>
#include <algorithm>
#include <filesystem>

#define BUF_SIZE 8192
#define HOST "127.0.0.1"
#define PORT 9090

using std::cin;
using std::cout;

class HeaderCreator {
public:
    HeaderCreator(AbstractModel *abstractModel): model(abstractModel) {}

    void makeGETrequestOnDownload(std::string &header);

    void makePOSTrequestOnUpload(std::string &header);

private:

    AbstractModel *model;
};

class BoostNetworkClient {
public:
    BoostNetworkClient(AbstractModel* abstractModel)
            : model(abstractModel){}

    void manageConnection();

private:
    boost::asio::io_service ioService;
    boost::asio::ip::tcp::socket sock {ioService};
    boost::asio::ip::tcp::endpoint endPoint;
    boost::asio::streambuf streamBuf;
    std::istream inputStreamFromBuf{&streamBuf};
    std::ofstream outputFileStream;
    std::size_t sizeOfBody{0};
    char buffer[BUF_SIZE];
    std::ifstream inputFileStream;
    unsigned long long fileSize;
    unsigned long long sentFileBody;
    AbstractModel* model;

    void handleConnection(boost::system::error_code const &ec);

    void handleReadHeader(boost::system::error_code const &ec, std::size_t bytesTransferred);

    void handleReadBody(boost::system::error_code const &ec, std::size_t bytesTransferred);

    void handleWriteHeader(boost::system::error_code const &ec, std::size_t transferred);

    void handleWriteBody(boost::system::error_code const &ec, std::size_t bytesTransferred);

    void cleanUp();
};


#endif //TLCONSOLEAPPLICATION_BOOSTNETWORK_H