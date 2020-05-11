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
            if (key == "KEYSTARTSYMBOL") {
                _keyStartSymbol = value[0];
            }
            if (key == "KEYENDSYMBOL") {
                _keyEndSymbol = value[0];
            }
            if (key == "PASSWORDSTARTSYMBOL") {
                _passwordStartSymbol = value[0];
            }
            if (key == "PASSWORDENDSYMBOL") {
                _passwordEndSymbol = value[0];
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
