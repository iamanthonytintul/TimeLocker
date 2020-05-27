#ifndef TIMELOCKER_RESOURCEMANAGERSTRINGCREATOR_H
#define TIMELOCKER_RESOURCEMANAGERSTRINGCREATOR_H

#include <string>
#include "resourceManager.h"

class ResourceManagerStringCreator: public AbstractResourceManager {
public:
    explicit ResourceManagerStringCreator(std::string_view path);
    ResourceManagerStringCreator(const ResourceManagerStringCreator&) = delete;
    void operator=(const ResourceManagerStringCreator&) = delete;

    void parseFile() override;
    int getKeySize() const;
    int getPasswordSize() const;
    char getKeyStartSymbol() const;
    char getKeyEndSymbol() const;
    char getPasswordStartSymbol() const;
    char getPasswordEndSymbol() const;
private:
    const std::string _pathToFile;
    int _keySize{};
    int _passwordSize{};
    char _keyStartSymbol{};
    char _keyEndSymbol{};
    char _passwordStartSymbol{};
    char _passwordEndSymbol{};
};

#endif //TIMELOCKER_RESOURCEMANAGERSTRINGCREATOR_H
