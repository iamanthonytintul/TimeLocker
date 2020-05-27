#include "View.h"

std::string HeaderHandler::pickFileName() {
    std::string fileName;
    std::string fileNameHeader = "filename=: ";
    size_t fileNamePos = headers.find(fileNameHeader);

    for (size_t i = fileNamePos+fileNameHeader.length(); headers[i] != '\n'; ++i) {
        fileName.push_back(headers[i]);
    }

    return fileName;
}

size_t HeaderHandler::pickFileLength() {
    std::string strFileLength;
    std::string fileLengthHeader = "Content-Length: ";
    size_t fileLengthPos = headers.find(fileLengthHeader);

    for (size_t i = fileLengthPos + fileLengthHeader.length(); headers[i] != '\n'; ++i) {
        strFileLength.push_back(headers[i]);
    }

    return std::stoi(strFileLength);
}

std::string HeaderHandler::pickFileKey() {
    std::string fileKey;
    std::string fileKeyHeader = "File-Key: ";
    size_t fileKeyPos = headers.find(fileKeyHeader);

    for (size_t i = fileKeyPos + fileKeyHeader.length(); headers[i] != '\n'; ++i) {
        fileKey.push_back(headers[i]);
    }

    return fileKey;
}

std::string HeaderHandler::pickServerResponse() {
    std::string serverResponse;
    std::string fileServerResponseHeader = "HTTP/1.1 ";
    size_t fileServerResponsePos = headers.find(fileServerResponseHeader);

    for (size_t i = fileServerResponsePos + fileServerResponseHeader.length(); headers[i] != '\n'; ++i) {
        serverResponse.push_back(headers[i]);
    }

    return serverResponse;
}
