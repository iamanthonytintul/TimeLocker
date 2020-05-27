#include "Web_Site.h"
#include "Content.h"


using namespace constants;


content::info_form::info_form() {
    input_pass.message("Enter password");
    input_file.message("Drop file");
    amountOfDays.message("Set lifetime");
    input_submit.value("Send!");
    input_file.limits(MIN_LIMIT, MAX_LIMIT);
    input_file.filename(booster::regex(MIME_REGEX));
    input_file.mime(ACCEPTABLE_MIME);
    amountOfDays.range(0,7);
    add(input_pass);
    add(amountOfDays);
    add(input_file);
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

int toInt(const std::string& toi){
    int res;
    try{
        res = std::stoi(toi);
    }catch(std::invalid_argument &e){
        res = DEFAULT_TIME;
    }return res;
}

int delimeterFunc(const std::string& req,std::string &key,std::string &val){
    if(req.empty())
        return FAIL;
    int delimeter_key = req.find(DELIMETER_KEY);
    if(delimeter_key == -1)
        return FAIL;
    key = req.substr(0, delimeter_key);
    unsigned long size = req.size() - delimeter_key;
    val = req.substr(delimeter_key + 1, size);
    return SUCCESS;
}


WebSite::WebSite(cppcms::service &s,AbstractController* _view,Logger* log) : cppcms::application(s),AbstractServer(_view,log) {
    dispatcher().assign("/get/(.*)", &WebSite::GetResponse, this, 1);
    dispatcher().assign("/post/", &WebSite::PostResponse, this);
    dispatcher().assign("/api/post/", &WebSite::APIPOSTResponse, this);
    dispatcher().assign("/api/get/", &WebSite::APIGETResponse, this);
    dispatcher().assign("/",&WebSite::StaticResponse, this);
}



void WebSite::PostResponse() {
    content::upload form;
    if(request().request_method() == "POST"){
        logger->debug("POST REQUEST");
        form.info.load(context());
        if(form.info.validate()){
            std::string pass = form.info.input_pass.value();
            int amountOfDays = form.info.amountOfDays.value();
            std::string name = view->PostData(pass,amountOfDays);
            if(name.empty()){
                logger->warning("SOMETHING WRONG WITH DATABASE");
                return(response().set_redirect_header("/"));
            }
            try {
                form.info.input_file.value()->save_to(PATH_TO_UPLOADS + name + FILE_TYPE);
                logger->debug("REQUEST FORM IS CORRECT. FILE UPLOADED " + name);
            }catch(std::exception e){
                logger->warning("SOMETHING INCORRECT WITH UPLOADING");
            }
            logger->debug("FILE UPLOADED WITH KEY AND PASS: " + name + ":" + pass );
            content::message res;
            res.link = name;
            res.pass = pass;
            return render("message",res);
        }
    }
    logger->debug("REQUEST FORM IS INCORRECT");
    return(response().set_redirect_header("/"));
}

void WebSite::GetResponse(std::string key) {
    content::getViaKeyFile form;
    if(request().request_method() == "GET"){
        logger->debug("GET REQUEST");
        return(render("getInfo",form));
    }
    else if(request().request_method() == "POST"){
        logger->debug("POST REQUEST ACCEPTED");
        form.info.load(context());
        if(form.info.validate()){
            logger->trace("POST FORM IS CORRECT");
            std::string pass = form.info.input_pass.value();
            int status = view->GetData(key,pass);
            if(status == 0 || !fileExists(PATH_TO_UPLOADS + key + FILE_TYPE)){
                logger->trace("INCORRECT DATA");
                return(response().set_redirect_header("/"));
            }logger->trace("CORRECT DATA: " + key + pass);

            response().add_header("X-Accel-Redirect",DOWNLOAD_PATH+key + FILE_TYPE);
            response().content_type(ACCEPTABLE_MIME);
            response().add_header("Content-Disposition: attachment; filename=file", FILE_TYPE);
            return response().set_redirect_header(DOWNLOAD_PATH);
        }
        logger->trace("INCORRECT FORM");
        return(response().set_redirect_header("/"));
    }
}

void WebSite::APIGETResponse() {
    if (request().request_method() == "GET") {
        logger->debug("GET REQUEST ACCEPTED");
        // получение ключа и пароля
        std::string auth_header = request().getenv(AUTHHEADER);
        std::string key,pass;
        if(delimeterFunc(auth_header,key,pass) == 0) {
            logger->trace("INCORRECT DATA REQUEST");
            return response().status(BAD_REQUEST);
        }
        //проверка пароля
        int status = view->GetData(key, pass);

        if (status == 0 || !fileExists(PATH_TO_UPLOADS + key + FILE_TYPE)) {
            logger->trace("INCORRECT DATA REQUEST");
            response().status(NOT_FOUND);
        }
        else {
            logger->trace("CORRECT DATA REQUEST. USED DATA: " + key + pass);
            response().add_header("X-Accel-Redirect",DOWNLOAD_PATH+key + FILE_TYPE);
            response().content_type(ACCEPTABLE_MIME);
            response().add_header("Content-Disposition: attachment; filename=",key + FILE_TYPE);
            return response().set_redirect_header(DOWNLOAD_PATH);
        }
    } else {
        logger->trace("INCORRECT METHOD");
        return response().status(METHOD_NOT_ALLOWED);
    }
}

void WebSite::APIPOSTResponse() {
    if (request().request_method() == "POST") {
        logger->debug("POST REQUEST ACCEPTED");
        if (int(request().files().size()) < MAX_LIMIT &&
                int(request().files().size()) > MIN_LIMIT) {
            //получение данных для корректного сохранения
            std::string pass = request().getenv(PASSHEADER);
            std::string lifeTime = request().getenv(TIMEHEADER);
            int amountOfDays = toInt(lifeTime);
            std::string name = view->PostData(pass,amountOfDays);
            try {
                request().files().data()->get()->save_to(PATH_TO_UPLOADS + name + FILE_TYPE);
            }catch(std::exception e){
                logger->warning("SOMETHING INCORRECT WITH UPLOADING");
            }
            logger->trace("RETURN DATA: " + name);
            response().add_header(FILEKEY,name);
            return response().status(SUCCESSFUL);
        } else {
            logger->debug("BAD REQUEST FILE");
            return response().status(BAD_REQUEST);
        }
    } else {
        logger->debug("INCORRECT REQUEST METHOD");
        return response().status(METHOD_NOT_ALLOWED);
    }
}

void WebSite::StaticResponse() {
    content::upload c;
    return render("upload",c);
}




