//
// Created by felix on 22.04.2020.
//

#ifndef BACKENDSERVICE_SERVER_H
#define BACKENDSERVICE_SERVER_H
#include "Controller.h"


class AbstractServer{
public:
    explicit AbstractServer(AbstractController* _view):view(_view){};
    virtual void GetResponse(std::string key) = 0;
    virtual void PostResponse() = 0;

    virtual void APIResponse(std::string key) = 0;

protected:
    AbstractController * view;
};

#endif //BACKENDSERVICE_SERVER_H