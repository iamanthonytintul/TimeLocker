#include "storage.h"

class StorageMySQL: public IDBManager {
public:
    StorageMySQL();
    ~StorageMySQL();
    int saveData(std::string path, std::string link, std::string key, std::string date) override;
    std::string getData(std::string link) override;
    bool deleteData(std::string link) override;
};

