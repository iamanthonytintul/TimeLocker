
#ifndef BACKENDSERVICE_SERVER_H
#define BACKENDSERVICE_SERVER_H
#include "Controller.hpp"


class AbstractServer{
public:
    explicit AbstractServer(AbstractController* _view,Logger* log):view(_view),logger(log){};
    virtual void GetResponse(std::string key) = 0;
    virtual void PostResponse() = 0;
    virtual void APIGETResponse() = 0;
    virtual void APIPOSTResponse() = 0;
    virtual void StaticResponse() = 0;

protected:
    AbstractController * view;
    Logger* logger;
};

#endif //BACKENDSERVICE_SERVER_H