#include "Model.h"

void Model::setFilePassword(const std::string &filePassword) {
    _filePassword = filePassword;
}

void Model::setFilePath(const std::string &filePath) {
    _filePath = filePath;
}

void Model::setFileKey(const std::string &fileKey) {
    _fileKey = fileKey;
}

void Model::setFileLifetime(const std::string& fileLifetime) {
    _fileLifetime = fileLifetime;
}

void Model::setApplicationMode(const std::string &appMode) {
    _applicationMode = appMode;
}

void Model::setExitMessage(const std::string &exitMessage) {
    _exitMessage = exitMessage;
}

const std::string &Model::getFilePassword() {
    return _filePassword;
}

const std::string &Model::getFilePath() {
    return _filePath;
}

const std::string &Model::getFileKey() {
    return _fileKey;
}

const std::string& Model::getFileLifetime() {
    return _fileLifetime;
}

const std::string& Model::getApplicationMode() {
    return _applicationMode;
}

const std::string &Model::getExitMessage() {
    return _exitMessage;
}
