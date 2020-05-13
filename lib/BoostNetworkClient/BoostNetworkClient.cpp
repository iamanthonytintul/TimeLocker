#include "view_presenter.h"

void BoostNetworkClient::handleReadBody(boost::system::error_code const &errorCode, std::size_t bytesTransferred) {

    if (errorCode && errorCode != boost::asio::error::eof) {
        throw std::runtime_error{
                "handleReadBody() : " + std::to_string(errorCode.value()) + ", " + errorCode.message()};
    }

    sizeOfBody += bytesTransferred;
    outputFileStream << &streamBuf;

    std::cout << "sizeOfBody = " << sizeOfBody << std::endl;

    if (sizeOfBody != fileSize && errorCode != boost::asio::error::eof) {

        boost::asio::async_read(sock, streamBuf, boost::asio::transfer_at_least(1),
                                [this](const boost::system::error_code &ec, std::size_t bytesTransferred) -> void {
                                        this->handleReadBody(ec, bytesTransferred);
                                });

    } else if (sizeOfBody == fileSize) {

        std::cout << "handleReadBody() : Transfer complete successfully" << std::endl;

    } else {

        throw std::runtime_error{
                "handleReadBody() : " + std::to_string(errorCode.value()) + ", " + errorCode.message()};

    }
}

void BoostNetworkClient::handleReadHeader(boost::system::error_code const &errorCode, std::size_t bytesTransferred) {
    if (errorCode) {
        throw std::runtime_error{
                "handleReadHeader() : " + std::to_string(errorCode.value()) + ", " + errorCode.message()};
    }

    std::string headers{std::istreambuf_iterator<char>{inputStreamFromBuf.rdbuf()}, {}};


    fileSize = std::filesystem::file_size(model->getFilePath());
    std::string fileName = std::filesystem::path{model->getFilePath()}.filename().string();
    std::string filePathToSave{std::filesystem::current_path().string() + fileName + std::filesystem::path{fileName}.extension().string() };

    outputFileStream.open(filePathToSave, std::ios::binary);
    if (!outputFileStream.is_open()) {
        throw std::runtime_error{"handleReadHeader() : Unable to open output file: " + filePathToSave};
    }

    if (sizeOfBody != fileSize) {

        boost::asio::async_read(sock, streamBuf, boost::asio::transfer_at_least(1),
                                [this](const boost::system::error_code &ec, std::size_t bytesTransferred) -> void {
                                    this->handleReadBody(ec, bytesTransferred);
                                });
    } else {
        std::cout << "handleReadHeader() : Transfer complete successfully" << std::endl;
    }

}

void BoostNetworkClient::handleWriteBody(boost::system::error_code const &errorCode, std::size_t bytesTransferred) {
    if (errorCode) {
        throw std::runtime_error{
                "handleWriteBody() : " + std::to_string(errorCode.value()) + ", " + errorCode.message()};
    }
    sentFileBody += bytesTransferred;
    if (inputFileStream) {

        inputFileStream.read(buffer, BUF_SIZE);
        boost::asio::async_write(sock, boost::asio::buffer(buffer, inputFileStream.gcount()),
                                 [this](const boost::system::error_code &ec,
                                        std::size_t bytesTransferred) -> void {
                                     this->handleWriteBody(ec, bytesTransferred);
                                 });

    } else {

        fileSize = std::filesystem::file_size(model->getFilePath());

        if (sentFileBody != fileSize) {
            throw std::runtime_error{"handleWriteBody(): sentFileBody != fileSize\n"};
        }

        std::cout << "OK" << std::endl;
    }
}

void BoostNetworkClient::handleWriteHeader(boost::system::error_code const &errorCode, std::size_t bytesTransferred) {
    if (errorCode) {
        throw std::runtime_error{
                "handleWriteHeader() : " + std::to_string(errorCode.value()) + ", " + errorCode.message()};
    }
    if (model->getApplicationMode()[FIRST_SYMBOL] == 'd') {
        boost::asio::async_read_until(sock, streamBuf, "\r\n\r\n",
                                      [this](const boost::system::error_code &ec,
                                             std::size_t bytesTransferred) -> void {
                                          this->handleReadHeader(ec, bytesTransferred);
                                      });
    } else {
    inputFileStream.read(buffer, std::size(buffer));
    boost::asio::async_write(sock, boost::asio::buffer(buffer, inputFileStream.gcount()),
                             [this](const boost::system::error_code &e,
                                    std::size_t transferred) -> void {
                                 this->handleWriteBody(e, transferred);
                             });
    }
}


void BoostNetworkClient::cleanUp() {

    try {
        inputFileStream.close();
        outputFileStream.close();
        sock.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        sock.close();
    }
    catch (std::exception &exception) {
        std::cerr << "Exception: " << exception.what() << std::endl;
    }

}

void BoostNetworkClient::handleConnection(const boost::system::error_code &errorCode) {

    std::string header{""};
    HeaderCreator *headerCreator = new HeaderCreator(model);

    if (model->getApplicationMode()[FIRST_SYMBOL] == DOWNLOAD_MODE) {

        headerCreator->makeGETrequestOnDownload(header);

    } else {
        inputFileStream.open(model->getFilePath(), std::ios::binary);

        headerCreator->makePOSTrequestOnUpload(header);

    }

    delete headerCreator;

    boost::asio::async_write(sock, boost::asio::buffer(header, header.size()),
                             [this](const boost::system::error_code &ec, std::size_t bytesTransferred) -> void {
                                 this->handleWriteHeader(ec, bytesTransferred);
                             });

}

void BoostNetworkClient::manageConnection() {
    try {
        sock.async_connect(boost::asio::ip::tcp::endpoint{boost::asio::ip::address::from_string(HOST), PORT},
                           [this](const boost::system::error_code &ec) -> void {
                               this->handleConnection(ec);
                           });
        ioService.run();
    }
    catch (std::exception &exception) {
        std::cerr << "Exception: " << exception.what() << std::endl;
    }

    cleanUp();
}
