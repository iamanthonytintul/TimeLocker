
#ifndef BACKENDSERVICE_CONTROLLER_HPP
#define BACKENDSERVICE_CONTROLLER_HPP

#include <iostream>
#include "stringCreator.h"
#include "Constant.h"
#include "Logger.h"
#include "querySet.h"
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
    Logger* logger;
    StringCreator* nmCreate;
public:
    ViewController(DataBaseType* _DBManager,Logger* log,StringCreator* creator):DBManager(_DBManager),logger(log),nmCreate(creator){};
    int GetData(std::string const& key, std::string const& pass) override;
    int ValidateData(std::string & key,std::string & pass) override;
    std::string PostData(std::string & pass,int amountOfDays) override;
};


template<class DataBaseType>
int ViewController<DataBaseType>::GetData(std::string const & key, std::string const & pass) {
    if(key.empty() || pass.empty()){
        logger->trace("INCORRECT INPUT DATA");
        return FAIL;
    }
    logger->trace("IN GETDATA WITH KEY: " + key);
    auto* querySet = new QuerySet;
    if(DBManager->getData(key,querySet) == EXIT_FAILURE){
        delete querySet;
        return FAIL;
    };
    std::map<std::string,std::string> res;
    if(querySet) {
        res = querySet->GetQuerySetRow();
        delete querySet;
    }  else {
        return FAIL;
    }
    if(res.empty() || pass != res[PASSMAP]){
        logger->trace("INCORRECT INPUT DATA");
        return FAIL;
    }
    return SUCCESS;
}

template<class DataBaseType>
int ViewController<DataBaseType>::ValidateData(std::string &key, std::string &pass){
    if(pass.empty()){
        logger->trace("PASSWORD CREATED");
        pass = nmCreate->createPassword();
    }
    std::map<std::string,std::string> result;
    do{
        key = nmCreate->createKey();
        logger->trace("CREATED KEY: " + key);
        auto* querySet = new QuerySet;
        DBManager->getData(key,querySet);
        if(querySet) {
            result = querySet->GetQuerySetRow();
            logger->trace("GOT ROW FROM DB: " + result[KEYMAP]);
            delete querySet;
        }
        else{
            logger->warning("SOMETHING WRONG WITH DATABASE");
            return FAIL;
        }
    }while(result[KEYMAP] == key);
    return SUCCESS;
}

template<class DataBaseType>
std::string ViewController<DataBaseType>::PostData(std::string & pass,int amountOfDays) {

    std::string DeletionDate = nmCreate->createDeletionDate(amountOfDays);
    std::string key;
    int status = ValidateData(key,pass);
    logger->trace("CREATED KEY:PASS -" + key + ":" + pass);
    if( status == FAIL || DBManager->saveData(key,pass,DeletionDate) == EXIT_FAILURE) {
        logger->trace("INCORRECT DATA CREATED");
        return "";
    }
    return key;
}

#endif //BACKENDSERVICE_CONTROLLER_HPP
