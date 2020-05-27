#ifndef TIMELOCKER_RESOURCEMANAGER_H
#define TIMELOCKER_RESOURCEMANAGER_H

#include <string>

class AbstractResourceManager {
public:
    virtual void parseFile() = 0;
private:
    const std::string _pathToFile;
};

#endif //TIMELOCKER_RESOURCEMANAGER_H
