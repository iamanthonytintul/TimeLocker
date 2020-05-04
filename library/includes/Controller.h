
#ifndef BACKEND_CONTROLLER_H
#define BACKEND_CONTROLLER_H

#include <iostream>
#include "NameCreator.h"

enum {NO_SUCH_FILE, NO_DB_CONNECTION};


class AbstractController{
public:
    virtual std::string GetData(std::string const&, std::string const&) = 0;
    virtual std::string PostData(std::string const &) = 0;
    virtual ~AbstractController() = default;
private:
    UniqueNameMaker nmCreate;
};


template <class DataBaseType>
class ViewController : public AbstractController{
    DataBaseType* DBManager;
public:
    explicit ViewController(DataBaseType* _DBManager):DBManager(_DBManager),AbstractController(){};
    std::string GetData(std::string const& key, std::string const& pass) override;
    std::string PostData(std::string const & pass) override;
};


#endif //BACKEND_CONTROLLER_H
