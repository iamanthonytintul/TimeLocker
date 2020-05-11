#include "Web_Site.h"
#include "Content.h"
#include "stringCreator.h"

#define DOWNLOAD_PATH "/uploads/"
#define ACCEPTABLE_MIME "application/zip"
#define FILE_TYPE ".zip"
#define BAD_REQUEST 400
#define NOT_FOUND 404
#define SUCCESSFUL 200
#define METHOD_NOT_ALLOWED 405


content::info_form::info_form() {
    input_pass.message("Enter password");
    input_file.message("Drop file");
    amountOfDays.message("Set amount of days");
    input_submit.value("Send!");
    input_file.limits(MIN_LIMIT, MAX_LIMIT);
    input_file.filename(booster::regex(".*\\.zip"));
    input_file.mime(ACCEPTABLE_MIME);
    amountOfDays.range(0,7);
    add(input_pass);
    add(input_file);
    add(amountOfDays);
    add(input_submit);
}

content::get_form::get_form() {
    input_key.message("Enter Key");
    input_pass.message("Enter password");
    input_submit.value("Send!");
    input_pass.non_empty();
    add(input_key);
    add(input_pass);
    add(input_submit);
}

content::pass_form::pass_form() {
    input_pass.message("Enter password");
    pass_submit.value("Send!");
    input_pass.non_empty();
    add(input_pass);
    add(pass_submit);
}

bool fileExists(const std::string& path){
    std::ifstream ifile(path.c_str());
    return (bool)ifile;
}

WebSite::WebSite(cppcms::service &s,AbstractController* _view) : cppcms::application(s),AbstractServer(_view) {
    dispatcher().assign("/get/(.*)", &WebSite::GetResponse, this, 1);
    dispatcher().assign("/post/", &WebSite::PostResponse, this);
    dispatcher().assign("/api/post/", &WebSite::APIPOSTResponse, this);
    dispatcher().assign("/api/get/", &WebSite::APIGETResponse, this);
    dispatcher().assign("/",&WebSite::StaticResponse, this);
}



void WebSite::PostResponse() {
    content::upload form;
    if(request().request_method() == "POST"){
        form.info.load(context());
        if(form.info.validate()){
            std::string pass = form.info.input_pass.value();
            int amountOfDays = form.info.amountOfDays.value();
            std::string name = view->PostData(pass,amountOfDays);
            form.info.input_file.value()->save_to(PATH_TO_UPLOADS + name + FILE_TYPE);
            std::cout << "file saved as" << PATH_TO_UPLOADS + name;
            content::message res;
            res.link = name;
            res.pass = pass;
            return render("message",res);
        }
    }
    return(response().set_redirect_header("/"));
}

void WebSite::GetResponse(std::string key) {
    content::getViaKeyFile form;
    if(request().request_method() == "GET"){
        return(render("getInfo",form));
    }
    else if(request().request_method() == "POST"){
        form.info.load(context());
        if(form.info.validate()){
            std::string pass = form.info.input_pass.value();
            std::string file_name = view->GetData(key,pass);
            if(file_name.empty() || !fileExists(PATH_TO_UPLOADS + file_name + FILE_TYPE)){
                return(response().set_redirect_header("/"));
            }
            response().add_header("X-Accel-Redirect",DOWNLOAD_PATH+file_name + FILE_TYPE);
            response().content_type(ACCEPTABLE_MIME);
            response().add_header("Content-Disposition: attachment; filename=",file_name + FILE_TYPE);
            return response().set_redirect_header(DOWNLOAD_PATH);
        }
        return(response().set_redirect_header("/"));
    }
}

void WebSite::APIGETResponse() {
    if (request().request_method() == "GET") {
        // getting key + pass from headers
        std::string auth_header = request().http_authorization();
        int delimeter_key = auth_header.find(':');
        std::string key = auth_header.substr(0, delimeter_key);
        unsigned long size = auth_header.size() - delimeter_key;
        std::string pass = auth_header.substr(delimeter_key, size);
        //validating pass from header
        std::string file_name = view->GetData(key, pass);
        if (file_name.empty() || !fileExists(PATH_TO_UPLOADS + file_name))
            response().status(NOT_FOUND);
        else {
            response().add_header("X-Accel-Redirect",DOWNLOAD_PATH+file_name + FILE_TYPE);
            response().content_type(ACCEPTABLE_MIME);
            response().add_header("Content-Disposition: attachment; filename=",file_name + FILE_TYPE);
            return response().set_redirect_header(DOWNLOAD_PATH);
        }
    } else {
        return response().status(METHOD_NOT_ALLOWED);
    }
}

void WebSite::APIPOSTResponse() {
    if (request().request_method() == "POST") {
        if (int(request().files().size()) < MAX_LIMIT && request().content_type() == ACCEPTABLE_MIME &&
            int(request().files().size()) > MIN_LIMIT) {
            std::string pass;
            int amountOfDays = 0;
            std::string name = view->PostData(pass,amountOfDays);
            request().files().data()->get()->save_to(PATH_TO_UPLOADS + name);
            return response().status(SUCCESSFUL);
        } else {
            return response().status(BAD_REQUEST);
        }
    } else {
        return response().status(METHOD_NOT_ALLOWED);
    }
}

void WebSite::StaticResponse() {
    content::upload c;
    return render("upload",c);
}




