#include <fstream>
#include <sstream>
#include "resourceManagerDatabase.h"

ResourceManagerDatabase::ResourceManagerDatabase(std::string_view path): _pathToFile(path) {
}

void ResourceManagerDatabase::parseFile() {
    std::ifstream resourceFile(_pathToFile);
    string line;
    while (std::getline(resourceFile, line)) {
        std::istringstream lineStream(line);
        std::string key;
        if (std::getline(lineStream, key, '=')) {
            std::string value;
            std::getline(lineStream, value);
            if (key == "HOST") {
                _host.append(value);
            }
            if (key == "USER") {
                _user.append(value);
            }
            if (key == "PASSWORD") {
                _password.append(value);
            }
            if (key == "DATABASE") {
                _database.append(value);
            }
        }
    }
}

string ResourceManagerDatabase::getHost() const {
    return _host;
}

string ResourceManagerDatabase::getUser() const {
    return _user;
}

string ResourceManagerDatabase::getPassword() const {
    return _password;
}

string ResourceManagerDatabase::getDatabase() const {
    return _database;
}
