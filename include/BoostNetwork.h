#ifndef TLCONSOLEAPPLICATION_BOOSTNETWORK_H
#define TLCONSOLEAPPLICATION_BOOSTNETWORK_H

#include <boost/asio.hpp>

class BoostNetworkClient : public AbstractNetworkClient {
public:
    explicit BoostNetworkClient(AbstractModel *abstractModel);

    void manageConnection() override;

private:
    boost::asio::io_service ioService;
    boost::asio::ip::tcp::socket sock{ioService};
    boost::asio::streambuf streamBuf;
    std::istream inputStreamFromBuf{&streamBuf};
    std::ofstream outputFileStream;
    std::ifstream inputFileStream;
    size_t sizeOfBody;
    size_t fileSize;
    size_t sizeOfSentFileBody;
    char buffer[BUF_SIZE];

    AbstractModel *model;

    void handleConnection(boost::system::error_code const &ec);

    void handleReadHeader(boost::system::error_code const &ec, std::size_t bytesTransferred);

    void handleReadBody(boost::system::error_code const &ec, std::size_t bytesTransferred);

    void handleWriteHeader(boost::system::error_code const &ec, std::size_t transferred);

    void handleWriteBody(boost::system::error_code const &ec, std::size_t bytesTransferred);

    void cleanUp() override;
};


#endif