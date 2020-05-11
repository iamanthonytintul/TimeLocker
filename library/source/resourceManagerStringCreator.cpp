#include <fstream>
#include <sstream>
#include <utility>
#include "resourceManagerStringCreator.h"

ResourceManagerStringCreator::ResourceManagerStringCreator(string path): _pathToFile(std::move(path)) {
}

void ResourceManagerStringCreator::parseFile() {
    std::ifstream infile(_pathToFile);
    string line;
    while (std::getline(infile, line)) {
        std::istringstream is_line(line);
        std::string key;
        if (std::getline(is_line, key, '=')) {
            std::string value;
            std::getline(is_line, value);
            if (key == "KEYSIZE") {
                _keySize = std::stoi(value);
            }
            if (key == "PASSWORDSIZE") {
                _passwordSize = std::stoi(value);
            }
        }
    }
}

int ResourceManagerStringCreator::getKeySize() const {
    return _keySize;
}

int ResourceManagerStringCreator::getPasswordSize() const {
    return _passwordSize;
}
