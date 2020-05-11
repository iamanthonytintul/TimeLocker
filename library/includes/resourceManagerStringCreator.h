#ifndef TIMELOCKER_RESOURCEMANAGERSTRINGCREATOR_H
#define TIMELOCKER_RESOURCEMANAGERSTRINGCREATOR_H
#include <iostream>
#include "resourceManager.h"

using std::string;

class ResourceManagerStringCreator: public AbstractResourceManager {
public:
    explicit ResourceManagerStringCreator(string path);
    ResourceManagerStringCreator(const ResourceManagerStringCreator&) = delete;
    void operator=(const ResourceManagerStringCreator&) = delete;
    ~ResourceManagerStringCreator() = default;

    void parseFile() override;
    int getKeySize() const;
    int getPasswordSize() const;
    char getKeyStartSymbol() const;
    char getKeyEndSymbol() const;
    char getPasswordStartSymbol() const;
    char getPasswordEndSymbol() const;
private:
    const string _pathToFile;
    int _keySize{};
    int _passwordSize{};
    char _keyStartSymbol{};
    char _keyEndSymbol{};
    char _passwordStartSymbol{};
    char _passwordEndSymbol{};
};

#endif //TIMELOCKER_RESOURCEMANAGERSTRINGCREATOR_H
