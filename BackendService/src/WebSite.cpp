#include "Web_Site.h"
#include "Content.h"
#include "NameCreator.h"


content::info_form::info_form() {
    input_pass.message("Enter password");
    input_file.message("Drop file");
    input_submit.value("Send!");
    input_pass.non_empty();
    input_file.limits(MIN_LIMIT, MAX_LIMIT);
    input_file.filename(booster::regex(".*\\.zip"));
    input_file.mime("application/zip");
    add(input_pass);
    add(input_file);
    add(input_submit);
}

content::get_form::get_form() {
    input_key.message("Enter Key");
    input_pass.message("Enter password");
    input_submit.value("Send!");
    input_key.non_empty();
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


void WebSite::PostResponse() {
    content::upload form;
    if(request().request_method() == "POST"){
        form.info.load(context());
        if(form.info.validate()){
            std::string pass = form.info.input_pass.value();
            std::string name = view->PostData(pass) + ".zip";
            form.info.input_file.value()->save_to(PATH_TO_UPLOADS + name);
            return(render());
        }
    }
    return(render())
}

void WebSite::GetResponse(std::string key) {
    content::getViaKey_file form;
    if(request().request_method() == "GET"){
        return(render())
    }
    else if(request().request_method() == "POST"){
        form.info.load(context());
        if(form.info.validate()){
            std::string pass = form.info.input_pass.value();
            std::string file_name = view->GetData(key,pass);
            if(file_name.empty()){
                return(render())
            }
            response().add_header("X-Accel-Redirect","/download/"+file_name);
            response().content_type("application/zip");
            response().add_header("Content-Disposition: attachment; filename=",file_name);
        }
    }
}

void WebSite::StaticResponse() {

}




