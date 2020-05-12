#ifndef TIMELOCKER_RESOURCEMANAGERDATABASE_H
#define TIMELOCKER_RESOURCEMANAGERDATABASE_H
#include <iostream>
#include "resourceManager.h"
using std::string;

class ResourceManagerDatabase: public AbstractResourceManager {
public:
    explicit ResourceManagerDatabase(string path);
    ResourceManagerDatabase(const ResourceManagerDatabase&) = delete;
    void operator=(const ResourceManagerDatabase&) = delete;
    ~ResourceManagerDatabase() override = default;

    void parseFile() override;
    string getHost() const;
    string getUser() const;
    string getPassword() const;
    string getDatabase() const;
private:
    const string _pathToFile;
    string _host;
    string _user;
    string _password;
    string _database;
};

#endif //TIMELOCKER_RESOURCEMANAGERDATABASE_H
