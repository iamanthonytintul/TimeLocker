#include <fstream>
#include <sstream>
#include "resourseManagerDatabase.h"

ResourceManagerDatabase::ResourceManagerDatabase(const string& path): _pathToFile(path) {
}

void ResourceManagerDatabase::parseFile() {
    std::ifstream infile(_pathToFile);
    string line;
    while (std::getline(infile, line)) {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) {
            std::string value;
            std::getline(is_line, value);
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
