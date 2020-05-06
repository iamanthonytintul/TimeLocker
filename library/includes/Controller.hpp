
#ifndef BACKENDSERVICE_CONTROLLER_HPP
#define BACKENDSERVICE_CONTROLLER_HPP

#include <iostream>
#include "NameCreator.h"
#include "storage.h"
#include <map>
enum {NO_SUCH_FILE, NO_DB_CONNECTION};


class AbstractController{
public:
    virtual std::string GetData(std::string const&, std::string const&) = 0;
    virtual std::string PostData(std::string const &, int amountOfDays) = 0;
    virtual ~AbstractController() = default;
protected:
    UniqueNameMaker nmCreate;
};


template <class DataBaseType>
class ViewController : public AbstractController{
    DataBaseType* DBManager;
public:
    explicit ViewController(DataBaseType* _DBManager):DBManager(_DBManager),AbstractController(){};
    std::string GetData(std::string const& key, std::string const& pass) override;
    std::string PostData(std::string const & pass,int amountOfDays) override;
};


template<class DataBaseType>
std::string ViewController<DataBaseType>::GetData(std::string const & key, std::string const & pass) {
    if(key.empty() || pass.empty()){
        return "";
    }
    std::map<std::string,std::string> res = DBManager->getData(key);
    if(res.empty() || pass != res["Password"]){
        return "";
    }
    return res["Key"];
}

template<class DataBaseType>
std::string ViewController<DataBaseType>::PostData(std::string const & pass,int amountOfDays) {
    std::string password;
    if(pass.empty()){
        password = nmCreate.createPassword();
    }
    std::string key = nmCreate.createKey();
    std::string DeletionDate = nmCreate.createDeletionDate(amountOfDays);
    while(DBManager->saveData(key,password,DeletionDate) == EXIT_FAILURE){
        key = nmCreate.createKey();
    };
    return key;
}

#endif //BACKENDSERVICE_CONTROLLER_HPP
