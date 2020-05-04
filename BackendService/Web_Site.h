
#ifndef BACKEND_WEB_SITE_H
#define BACKEND_WEB_SITE_H

#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/http_file.h>
#include "Controller.h"
#include "Server.h"

class WebSite:public cppcms::application,public AbstractServer{
public:
    explicit WebSite(cppcms::service &s,AbstractController* _view) : cppcms::application(s),AbstractServer(_view){
        dispatcher().assign("/get/(\\d+)",&WebSite::GetResponse,this,1);
        dispatcher().assign("/post/",&WebSite::PostResponse, this);
    };
    void GetResponse(std::string key) override;
    void PostResponse() override;
    void APIResponse(std::string key);
};


#endif //BACKEND_WEB_SITE_H