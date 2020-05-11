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
private:
    const string _pathToFile;
    int _keySize{};
    int _passwordSize{};
};

#endif //TIMELOCKER_RESOURCEMANAGERSTRINGCREATOR_H
