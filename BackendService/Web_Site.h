
#ifndef BACKEND_WEB_SITE_H
#define BACKEND_WEB_SITE_H

#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/http_file.h>
#include "Controller.hpp"
#include "Server.h"

class WebSite:public cppcms::application,public AbstractServer{
public:
    WebSite(cppcms::service &s,AbstractController* _view);
    void GetResponse(std::string key) override;
    void PostResponse() override;
    void APIGETResponse() override;
    void APIPOSTResponse() override;
    void StaticResponse() override;
};


#endif //BACKEND_WEB_SITE_H