#include <iostream>
#include <Web_Site.h>
#include <Controller.h>

int main(int argc, char* argv[]){
    try{
        cppcms::service srv(argc,argv);
        srv.applications_pool().mount(cppcms::applications_factory<WebSite>());
        srv.run();
    }catch(std::exception const &e){
        std::cerr<<e.what() << std::endl;
    }
    return 0;
}