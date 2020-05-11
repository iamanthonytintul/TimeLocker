
#ifndef BACKENDSERVICE_CONTROLLER_HPP
#define BACKENDSERVICE_CONTROLLER_HPP

#include <iostream>
#include "stringCreator.h"
#include "storage.h"
#include <map>
enum {NO_SUCH_FILE, NO_DB_CONNECTION};


class AbstractController{
public:
    virtual std::string GetData(std::string const&, std::string const&) = 0;
    virtual std::string PostData(std::string  &, int amountOfDays) = 0;
    virtual ~AbstractController() = default;
protected:
    StringCreator nmCreate;
};


template <class DataBaseType>
class ViewController : public AbstractController{
    DataBaseType* DBManager;
public:
    explicit ViewController(DataBaseType* _DBManager):DBManager(_DBManager),AbstractController(){};
    std::string GetData(std::string const& key, std::string const& pass) override;
    std::string PostData(std::string & pass,int amountOfDays) override;
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
std::string ViewController<DataBaseType>::PostData(std::string & pass,int amountOfDays) {
    if(pass.empty()){
        pass = nmCreate.createPassword();
    }
    std::string DeletionDate = nmCreate.createDeletionDate(amountOfDays);
    std::map<std::string,std::string> result;
    std::string key;
    do{
        key = nmCreate.createKey();
        result = DBManager->getData(key);
    }while(result["Key"] == key);
    DBManager->saveData(key,pass,DeletionDate);
    std::cout << pass << std::endl;
    return key;
}

#endif //BACKENDSERVICE_CONTROLLER_HPP
