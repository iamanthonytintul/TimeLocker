
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
#include "Logger.h"

class WebSite:public cppcms::application,public AbstractServer{
public:
    WebSite(cppcms::service &s,AbstractController* _view,Logger* log);
    void GetResponse(std::string key) override;
    void PostResponse() override;
    void APIGETResponse() override;
    void APIPOSTResponse() override;
    void StaticResponse() override;
};

bool fileExists(const std::string& path);
int toInt(const std::string& toi);
int delimeterFunc(const std::string& req,std::string &key,std::string &val);


#endif //BACKEND_WEB_SITE_H