
#ifndef BACKEND_WEB_SITE_H
#define BACKEND_WEB_SITE_H

#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include "Controller.h"


class WebSite:public cppcms::application{
    AbstractController* view;
public:
    explicit WebSite(cppcms::service &s,AbstractController* _view) : cppcms::application(s),view(_view){};
    int Response(std::string key);
};

#endif //BACKEND_WEB_SITE_H