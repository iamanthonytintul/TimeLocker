//
// Created by felix on 15.04.2020.
//

#ifndef BACKENDSERVICE_NAMECREATOR_H
#define BACKENDSERVICE_NAMECREATOR_H
#include <iostream>


class NameCreator{
public:
    virtual std::string createKey() = 0;
    virtual std::string createPassword() = 0;
    virtual std::string createDeletionDate(int day) = 0;
};


class UniqueNameMaker:public NameCreator{
public:
    std::string createKey() override;
    std::string createPassword() override;
    std::string createDeletionDate(int day) override;
};



#endif //BACKENDSERVICE_NAMECREATOR_H
