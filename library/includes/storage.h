#ifndef TIMELOCKER_STORAGE_H
#define TIMELOCKER_STORAGE_H

template <typename QuerySet, typename Logger>
class AbstractDBManager {
public:
    virtual int connect(string host, string user, string password, string database, Logger*& logger) = 0;
    virtual int saveData(string key, string password, string deletionDate, Logger*& logger) = 0;
    virtual int getData(string key, QuerySet*& querySet, Logger*& logger) = 0;
    virtual bool isConnected() = 0;
};

#endif
