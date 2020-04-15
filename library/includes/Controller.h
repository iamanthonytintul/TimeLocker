
#ifndef BACKEND_CONTROLLER_H
#define BACKEND_CONTROLLER_H

#include <iostream>
#include "NameCreator.h"

enum {NO_SUCH_FILE, NO_DB_CONNECTION};


class AbstractController{
public:
    virtual char* GetData(std::string const&, std::string const&) = 0;
    virtual int PostData(std::string const &) = 0;
    virtual ~AbstractController() = default;
};


template <class DataBaseType>
class ViewController : public AbstractController{
    UniqueNameMaker nmCreate;
    DataBaseType* DBManager;
public:
    explicit ViewController(DataBaseType* _DBManager):DBManager(_DBManager){
        nmCreate = UniqueNameMaker();
    };
    char* GetData(std::string const&, std::string const&) override;
    int PostData(std::string const &) override;
};


#endif //BACKEND_CONTROLLER_H
