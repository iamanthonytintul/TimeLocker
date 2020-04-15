#ifndef TIMELOCKER_STORAGE_H
#define TIMELOCKER_STORAGE_H
#include <iostream>
#define SUCCESS 0

template <class Database>
class IStorage {
public:
    virtual ~IStorage() = default;
    virtual std::string getPathToFile(std::string link) = 0;
    virtual bool isUniqueLink(std::string link) = 0;
    virtual bool isValidLink(std::string link) = 0;
    virtual bool isCorrectKey(std::string link, std::string key) = 0;
private:
    Database* DBManager;
};

class IDBManager {
public:
    virtual ~IDBManager() = default;
    virtual int saveData(std::string path, std::string link, std::string key, std::string date) = 0;
    virtual std::string getData(std::string link) = 0;
    virtual bool deleteData(std::string link) = 0;
};

template <class Database>
class IStorageDateInspector {
public:
    virtual ~IStorageDateInspector() = default;
    virtual int checkDeletionDate(std::string link) = 0;
private:
    Database* DBManager;
};

template <class Database>
class Storage: public IStorage<Database> {
public:
    Storage(Database* database) {}
    std::string getPathToFile(std::string link) override;
    bool isUniqueLink(std::string link) override;
    bool isValidLink(std::string link) override;
    bool isCorrectKey(std::string link, std::string key) override;
private:
    Database* DBManager;
};

template <class Database>
std::string Storage<Database>::getPathToFile(std::string link) {
    std::string path = "/usr/bin/file.txt";
    return path;
}

template <class Database>
bool Storage<Database>::isValidLink(std::string link) {
    return true;
}

template <class Database>
bool Storage<Database>::isUniqueLink(std::string link) {
    return true;
}

template <class Database>
bool Storage<Database>::isCorrectKey(std::string link, std::string key) {
    return true;
}

template <class Database>
class StorageDateInspector: public IStorageDateInspector<Database> {
public:
    StorageDateInspector(Database* database) {}
    int checkDeletionDate(std::string link) override;
private:
    Database* DBManager;
};

template <class Database>
int StorageDateInspector<Database>::checkDeletionDate(std::string link) {
    return SUCCESS;
}

#endif
