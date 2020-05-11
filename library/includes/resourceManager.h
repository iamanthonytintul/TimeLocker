#ifndef TIMELOCKER_RESOURCEMANAGER_H
#define TIMELOCKER_RESOURCEMANAGER_H
#include <iostream>

class AbstractResourceManager {
public:
    ~AbstractResourceManager() = default;
    virtual void parseFile() = 0;
private:
    const std::string _pathToFile;
};

#endif //TIMELOCKER_RESOURCEMANAGER_H
