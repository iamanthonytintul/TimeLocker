#include <iostream>
#include <Web_Site.h>
#include <Controller.hpp>
#include <storageMYSQL.hpp>


int main(int argc, char* argv[]){
    std::map<std::string,std::string>result;
    auto* database = new StorageMySQL<std::map<std::string,std::string>>;
    auto* view = new ViewController<StorageMySQL<std::map<std::string,std::string>>>(database);
    try{
        cppcms::service srv(argc,argv);
        booster::intrusive_ptr<WebSite> c=new WebSite(srv,view);
        srv.applications_pool().mount(c);
        srv.run();
    }catch(std::exception const &e){
        std::cerr<<e.what() << std::endl;
    }
    delete database;
    delete view;
    return 0;
}