#include <iostream>
#include "View.h"
#include "BoostNetwork.h"

int main(int argc, char *argv[]) {

    AbstractModel* model = new Model();
    AbstractNetworkClient *networkClient = new BoostNetworkClient{model};
    auto* applicationPresenter = new ApplicationPresenter{model, networkClient};
    applicationPresenter->start();

    delete model;
    delete networkClient;
    delete applicationPresenter;
    return 0;
}
