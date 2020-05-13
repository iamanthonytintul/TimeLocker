#include <iostream>
#include "view_presenter.h"

int main(int argc, char *argv[]) {

    AbstractModel* model = new Model();
    ApplicationPresenter* applicationPresenter = new ApplicationPresenter{model};

    applicationPresenter->start();
    BoostNetworkClient *boostNetworkClient = new BoostNetworkClient{model};
    boostNetworkClient->manageConnection();

    return 0;
}
