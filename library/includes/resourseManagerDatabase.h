#ifndef TIMELOCKER_RESOURSEMANAGERDATABASE_H
#define TIMELOCKER_RESOURSEMANAGERDATABASE_H
#include <iostream>

using std::string;

class ResourceManagerDatabase {
public:
    explicit ResourceManagerDatabase(const string& path);
    ResourceManagerDatabase(const ResourceManagerDatabase&) = delete;
    void operator=(const ResourceManagerDatabase&) = delete;
    ~ResourceManagerDatabase() = default;

    void parseFile();
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

#endif //TIMELOCKER_RESOURSEMANAGERDATABASE_H
