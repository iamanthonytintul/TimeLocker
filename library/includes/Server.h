//
// Created by felix on 22.04.2020.
//

#ifndef BACKENDSERVICE_SERVER_H
#define BACKENDSERVICE_SERVER_H
#include "Controller.hpp"


class AbstractServer{
public:
    explicit AbstractServer(AbstractController* _view):view(_view){};
    virtual void GetResponse(std::string key) = 0;
    virtual void PostResponse() = 0;
    virtual void APIGETResponse() = 0;
    virtual void APIPOSTResponse() = 0;
    virtual void StaticResponse() = 0;

protected:
    AbstractController * view;
};

#endif //BACKENDSERVICE_SERVER_H