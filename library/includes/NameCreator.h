//
// Created by felix on 15.04.2020.
//

#ifndef BACKENDSERVICE_NAMECREATOR_H
#define BACKENDSERVICE_NAMECREATOR_H
#include <iostream>


class NameCreator{
public:
    virtual std::string createKey(std::string name) = 0;
};


class UniqueNameMaker:public NameCreator{
public:
    std::string createKey(std::string name) override;
};



#endif //BACKENDSERVICE_NAMECREATOR_H
