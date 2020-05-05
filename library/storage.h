#ifndef TIMELOCKER_STORAGE_H
#define TIMELOCKER_STORAGE_H

template <typename DBRow>
class IDBManager {
public:
    virtual ~IDBManager() = default;
    virtual int saveData(std::string key, std::string password, std::string deletionDate) = 0;
    virtual DBRow getData(std::string key) = 0;
    virtual bool isConnected() = 0;
};

#endif
