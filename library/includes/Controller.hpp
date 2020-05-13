
#ifndef BACKENDSERVICE_CONTROLLER_HPP
#define BACKENDSERVICE_CONTROLLER_HPP

#include <iostream>
#include "stringCreator.h"
#include "storage.h"
#include "Constant.h"
#include <map>

using namespace constants;

class AbstractController{
public:
    virtual int GetData(std::string const&, std::string const&) = 0;
    virtual std::string PostData(std::string  &, int amountOfDays) = 0;
    virtual int ValidateData(std::string & key,std::string &pass) = 0;
    virtual ~AbstractController() = default;
};


template <class DataBaseType>
class ViewController : public AbstractController{
    DataBaseType* DBManager;
    StringCreator nmCreate;
public:
    explicit ViewController(DataBaseType* _DBManager):DBManager(_DBManager) {};
    int GetData(std::string const& key, std::string const& pass) override;
    int ValidateData(std::string & key,std::string & pass) override;
    std::string PostData(std::string & pass,int amountOfDays) override;
};


template<class DataBaseType>
int ViewController<DataBaseType>::GetData(std::string const & key, std::string const & pass) {
    if(key.empty() || pass.empty()){
        return FAIL;
    }
    std::map<std::string,std::string> res = DBManager->getData(key);

    if(res.empty() || pass != res[PASSMAP]){
        return FAIL;
    }
    return SUCCESS;
}

template<class DataBaseType>
int ViewController<DataBaseType>::ValidateData(std::string &key, std::string &pass){
    if(pass.empty()){
        pass = nmCreate.createPassword();
    }
    std::map<std::string,std::string> result;
    do{
        key = nmCreate.createKey();
        result = DBManager->getData(key);
    }while(result[KEYMAP] == key);
    return SUCCESS;
}

template<class DataBaseType>
std::string ViewController<DataBaseType>::PostData(std::string & pass,int amountOfDays) {

    std::string DeletionDate = nmCreate.createDeletionDate(amountOfDays);
    std::string key;
    ValidateData(key,pass);

    if(DBManager->saveData(key,pass,DeletionDate) == EXIT_FAILURE)
        return "";
    std::cout << pass << std::endl;
    return key;
}

#endif //BACKENDSERVICE_CONTROLLER_HPP
