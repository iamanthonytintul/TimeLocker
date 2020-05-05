#include <iostream>
#include <Web_Site.h>
#include <Controller.hpp>

int main(int argc, char* argv[]){
    try{
        cppcms::service srv(argc,argv);
        ViewController<DataBaseType> view(DBManager);
        srv.applications_pool().mount(cppcms::applications_factory<WebSite>(vie w));
        srv.run();
    }catch(std::exception const &e){
        std::cerr<<e.what() << std::endl;
    }
    return 0;
}