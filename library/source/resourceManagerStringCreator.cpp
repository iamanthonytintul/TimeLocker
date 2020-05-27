#include <fstream>
#include <sstream>
#include "resourceManagerStringCreator.h"

const int SYMBOL = 0;

ResourceManagerStringCreator::ResourceManagerStringCreator(std::string_view path): _pathToFile(path) {
}

void ResourceManagerStringCreator::parseFile() {
    std::ifstream resourceFile(_pathToFile);
    std::string line;
    while (std::getline(resourceFile, line)) {
        std::istringstream lineStream(line);
        std::string key;
        if (std::getline(lineStream, key, '=')) {
            std::string value;
            std::getline(lineStream, value);
            if (key == "KEY_SIZE") {
                _keySize = std::stoi(value);
            }
            if (key == "PASSWORD_SIZE") {
                _passwordSize = std::stoi(value);
            }
            if (key == "KEY_START_SYMBOL") {
                _keyStartSymbol = value[SYMBOL];
            }
            if (key == "KEY_END_SYMBOL") {
                _keyEndSymbol = value[SYMBOL];
            }
            if (key == "PASSWORD_START_SYMBOL") {
                _passwordStartSymbol = value[SYMBOL];
            }
            if (key == "PASSWORD_END_SYMBOL") {
                _passwordEndSymbol = value[SYMBOL];
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

char ResourceManagerStringCreator::getKeyStartSymbol() const {
    return _keyStartSymbol;
}

char ResourceManagerStringCreator::getKeyEndSymbol() const {
    return _keyEndSymbol;
}

char ResourceManagerStringCreator::getPasswordStartSymbol() const {
    return _passwordStartSymbol;
}

char ResourceManagerStringCreator::getPasswordEndSymbol() const {
    return _passwordEndSymbol;
}
