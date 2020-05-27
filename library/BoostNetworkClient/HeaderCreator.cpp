#include "View.h"

void HeaderCreator::makeGETRequestOnDownload(std::string &header) {

    std::stringstream headerStream;
    headerStream << "GET " << GET_ADDRESS << " HTTP/1.1" << REQUEST_NEW_LINE
                 << "Host: " << HOST << REQUEST_NEW_LINE
                 << "Authorization: " << model->getFileKey() << ":" << model->getFilePassword() << REQUEST_HEADER_END;
    header = headerStream.str();

}

void HeaderCreator::makePOSTRequestOnUpload(std::string &header) {

    std::filesystem::path pathToUploadFile = std::filesystem::path(model->getFilePath());
    size_t contentLength =
            std::filesystem::file_size(pathToUploadFile) + pathToUploadFile.filename().string().size() +
            POST_REQUEST_BODY_SIZE;
    std::string fileName = pathToUploadFile.filename().string();

    std::stringstream headerStream;
    headerStream << "POST " << POST_ADDRESS << " HTTP/1.1" << REQUEST_NEW_LINE
                 << "Host: " << HOST << ":" << std::to_string(PORT) << REQUEST_NEW_LINE
                 << "Content-Type: multipart/form-data; boundary=" << TIMELOCKER_BOUNDARY << REQUEST_NEW_LINE
                 << "Content-Length: " << contentLength << REQUEST_NEW_LINE
                 << "File-Lifetime: " << model->getFileLifetime() << REQUEST_NEW_LINE
                 << "File-Password: " << model->getFilePassword() << REQUEST_HEADER_END
                 << "--" << TIMELOCKER_BOUNDARY << REQUEST_NEW_LINE
                 << "Content-Disposition: form-data; name=\"text\"; filename=\""
                 << fileName << "\"" << REQUEST_NEW_LINE
                 << "Content-Type: text/plain" << REQUEST_HEADER_END;

    header = headerStream.str();
}

