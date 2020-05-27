#include <iostream>
#include <Web_Site.h>
#include <Controller.hpp>
#include <storageMYSQL.hpp>
#include "Logger.h"
#include "resourceManagerStringCreator.h"
#include "resourceManagerDatabase.h"


int main(int argc, char* argv[]){
    auto* querySet = new QuerySet;
    auto*resourceManagerDatabase = new ResourceManagerDatabase(PATH_TO_DB_CONFIG);
    resourceManagerDatabase->parseFile();
    ResourceManagerStringCreator resourceManagerStringCreator(PATH_TO_STRING_CREATOR);
    resourceManagerStringCreator.parseFile();
    auto* creator = new StringCreator(resourceManagerStringCreator.getKeySize(),
                                resourceManagerStringCreator.getPasswordSize(),
                                resourceManagerStringCreator.getKeyStartSymbol(),
                                resourceManagerStringCreator.getKeyEndSymbol(),
                                resourceManagerStringCreator.getPasswordStartSymbol(),
                                resourceManagerStringCreator.getPasswordEndSymbol());
    auto* database = new StorageMySQL<QuerySet>;
    database->connect(resourceManagerDatabase->getHost(),
                      resourceManagerDatabase->getUser(),
                      resourceManagerDatabase->getPassword(),
                      resourceManagerDatabase->getDatabase());
    std::map<std::string,std::string>result;
    auto* log = new Logger("log.txt");
    auto* view = new ViewController<StorageMySQL<QuerySet> >(database,log,creator);
    try{
        cppcms::service srv(argc,argv);
        booster::intrusive_ptr<WebSite> c=new WebSite(srv,view,log);
        srv.applications_pool().mount(c);
        srv.run();
    }catch(std::exception const &e){
        std::cerr<<e.what() << std::endl;
    }
    delete database;
    delete view;
    delete log;
    delete creator;
    delete querySet;
    delete resourceManagerDatabase;
    return 0;
}