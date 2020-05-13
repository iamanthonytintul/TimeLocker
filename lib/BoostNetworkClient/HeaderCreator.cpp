#include "view_presenter.h"

void HeaderCreator::makeGETrequestOnDownload(std::string &header) {

    std::string address = "/api/get/";
    std::stringstream headerStream{
            "GET " + address + " HTTP/1.1" + "\r\n" +
            "Host: " + HOST + "\r\n" +
            "Authorization: " + model->getFileKey() + ":" + model->getFilePassword() + "\r\n\r\n"};
    header = headerStream.str();

}

void HeaderCreator::makePOSTrequestOnUpload(std::string &header) {

    std::string address = "/api/post/";
    std::stringstream headerStream{
            "GET " + address + " HTTP/1.1" + "\r\n" +
            "Host: " + HOST + "\r\n" +
            "Content-Type: multipart/form-data" + "\r\n" +
            "Content-Length: " + std::to_string(std::filesystem::file_size(model->getFilePath())) + "\r\n" +
            "File-Name: " + std::filesystem::path{model->getFilePath()}.filename().string() + "\r\n" +
            "File-Lifetime: " + model->getFileLifetime() + "\r\n" +
            "File-Password: " + model->getFilePassword() + "\r\n\r\n"
    };
    header = headerStream.str();

}
