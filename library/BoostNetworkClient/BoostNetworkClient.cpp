#include "View.h"
#include "BoostNetwork.h"

BoostNetworkClient::BoostNetworkClient(AbstractModel *abstractModel) : model(abstractModel) {}

void BoostNetworkClient::handleReadBody(boost::system::error_code const &errorCode, std::size_t bytesTransferred) {

    if (errorCode && errorCode != boost::asio::error::eof) {
        throw std::runtime_error{"Error: " + errorCode.message()};
    }

    sizeOfBody += bytesTransferred;
    outputFileStream << &streamBuf;

    if (sizeOfBody != fileSize && errorCode != boost::asio::error::eof) {

        boost::asio::async_read(sock, streamBuf, boost::asio::transfer_at_least(TRANSFER_AT_LEAST_NUMBER),
                                [this](const boost::system::error_code &ec, std::size_t bytesTransferred) -> void {
                                    this->handleReadBody(ec, bytesTransferred);
                                });

    } else if (sizeOfBody == fileSize) {
        model->setExitMessage("Transfer complete successfully");
    } else {
        throw std::runtime_error{"Error: " + errorCode.message()};
    }
}

void BoostNetworkClient::handleReadHeader(boost::system::error_code const &errorCode, std::size_t bytesTransferred) {
    if (errorCode) {
        throw std::runtime_error{"Error: " + errorCode.message()};
    }

    std::string firstRequest{std::istreambuf_iterator<char>{inputStreamFromBuf.rdbuf()}, {}};
    size_t headerEndPosition = firstRequest.find(REQUEST_HEADER_END) + std::size(REQUEST_HEADER_END);
    std::string headers{firstRequest.substr(FIRST_SYMBOL, headerEndPosition)};

    HeaderHandler headerHandler{model, headers};

    sizeOfBody += bytesTransferred - headerEndPosition;

    if (headerHandler.pickServerResponse() != OK_RESPONSE) {
        throw std::runtime_error{"An error has occurred. Please check the entered data and try again"};
    }

    if (model->getApplicationMode()[FIRST_SYMBOL] == DOWNLOAD_MODE) {

        model->setFilePath(std::filesystem::current_path().string() + "/" + headerHandler.pickFileName());
        fileSize = headerHandler.pickFileLength();
        outputFileStream.open(model->getFilePath(), std::ios::binary);

        if (!outputFileStream.is_open()) {
            throw std::runtime_error{"Error: Unable to open output file: " + model->getFilePath()};
        }
        outputFileStream << firstRequest.substr(headerEndPosition);

    } else {
        model->setFileKey(headerHandler.pickFileKey());
        fileSize = 0;
    }

    if (sizeOfBody != fileSize) {

        boost::asio::async_read(sock, streamBuf, boost::asio::transfer_at_least(TRANSFER_AT_LEAST_NUMBER),
                                [this](const boost::system::error_code &ec, std::size_t bytesTransferred) -> void {
                                    this->handleReadBody(ec, bytesTransferred);
                                });

    } else if (fileSize == 0) {
        model->setExitMessage("Transfer complete successfully. Your file key: " + model->getFileKey());
    } else {
        model->setExitMessage("Transfer complete successfully");
    }


}
void BoostNetworkClient::handleWriteBody(boost::system::error_code const &errorCode, std::size_t bytesTransferred) {
    if (errorCode) {
        throw std::runtime_error{"Error: " + errorCode.message()};
    }

    sizeOfSentFileBody += bytesTransferred;
    if (inputFileStream) {

        inputFileStream.read(buffer, BUF_SIZE);
        boost::asio::async_write(sock, boost::asio::buffer(buffer, inputFileStream.gcount()),
                                 [this](const boost::system::error_code &ec,
                                        std::size_t bytesTransferred) -> void {
                                     this->handleWriteBody(ec, bytesTransferred);
                                 });

    } else {

        fileSize = std::filesystem::file_size(model->getFilePath());
        if (sizeOfSentFileBody != fileSize) {
            throw std::runtime_error{"Error: Outgoing file size does not equal the file size"};
        } else {
            boost::asio::async_write(sock, boost::asio::buffer(POST_REQUEST_ENDING, std::size(POST_REQUEST_ENDING)),
                                     [this](const boost::system::error_code &ec, std::size_t bytesTransferred) -> void {
                                         if (ec) {
                                             throw std::runtime_error{"Error: " + ec.message()};
                                         }
                                     });
        }
    }
}

void BoostNetworkClient::handleWriteHeader(boost::system::error_code const &errorCode, std::size_t bytesTransferred) {
    if (errorCode) {
        throw std::runtime_error{"Error: " + errorCode.message()};
    }
    if (model->getApplicationMode()[FIRST_SYMBOL] == DOWNLOAD_MODE) {
        boost::asio::async_read(sock, streamBuf, boost::asio::transfer_at_least(1),
                                [this](const boost::system::error_code &ec, std::size_t bytesTransferred) -> void {
                                    this->handleReadHeader(ec, bytesTransferred);
                                });
    } else {
        inputFileStream.read(buffer, std::size(buffer));
        boost::asio::async_write(sock, boost::asio::buffer(buffer, inputFileStream.gcount()),
                                 [this](const boost::system::error_code &ec,
                                        std::size_t transferred) -> void {
                                     this->handleWriteBody(ec, transferred);
                                 });
        boost::asio::async_read_until(sock, streamBuf, "\r\n\r\n",
                                      [this](const boost::system::error_code &ec,
                                             std::size_t bytesTransferred) -> void {
                                          this->handleReadHeader(ec, bytesTransferred);
                                      });
    }

}


void BoostNetworkClient::cleanUp() {

    try {
        inputFileStream.close();
        outputFileStream.close();
        sock.close();
    }
    catch (std::exception &exception) {
        model->setExitMessage(exception.what());
    }

}

void BoostNetworkClient::handleConnection(const boost::system::error_code &errorCode) {

    std::string header;
    HeaderCreator headerCreator{model};

    if (model->getApplicationMode()[FIRST_SYMBOL] == DOWNLOAD_MODE) {
        headerCreator.makeGETRequestOnDownload(header);
    } else {
        inputFileStream.open(model->getFilePath(), std::ios::binary);
        headerCreator.makePOSTRequestOnUpload(header);
    }

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
        model->setExitMessage(exception.what());
    }

    cleanUp();
}
