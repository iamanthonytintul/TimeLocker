#include "View.h"

int ApplicationPresenter::start() {
    AbstractView *startPage = new ConsoleViewStartPage{this,input, output};

    startPage->printPage();

    int errorCode = setApplicationMode();

    delete startPage;
    return errorCode;
}

int ApplicationPresenter::setApplicationMode() {
    AbstractView *appModePage = new ConsoleViewSetApplicationModePage{this,input, output};

    appModePage->printPage();

    int errorCode = SUCCESS;

    model->setApplicationMode(enteredData);

    if (enteredData[FIRST_SYMBOL] == DOWNLOAD_MODE) {
        errorCode |= setDownloadInfo();
    } else {
        errorCode |= setUploadInfo();
    }

    delete appModePage;
    return errorCode;
}

int ApplicationPresenter::setDownloadInfo() {

    int errorCode = SUCCESS;

    AbstractView *downloadInfo = new ConsoleViewDownloadFileMessagePage{this,input, output};
    errorCode |= downloadInfo->printPage();

    AbstractView *setKeyPage = new ConsoleViewSetKeyPage{this,input, output};
    errorCode |= setKeyPage->printPage();

    model->setFileKey(enteredData);

    AbstractView *setPasswordPage = new ConsoleViewSetPasswordPage{this,input, output};
    errorCode |= setPasswordPage->printPage();

    model->setFilePassword(enteredData);


    networkClient->manageConnection();

    AbstractShowInfoView *infoView = new ConsoleViewExitMessagePage{output};
    infoView->printInfo(model->getExitMessage());

    delete downloadInfo;
    delete setKeyPage;
    delete setPasswordPage;
    delete infoView;
    return errorCode;
}

int ApplicationPresenter::setEnteredData(std::string &data) {

    enteredData = data;
    return SUCCESS;
}

int ApplicationPresenter::setUploadInfo() {

    int errorCode = SUCCESS;

    AbstractView *uploadInfo = new ConsoleViewUploadFileMessagePage{this,input, output};
    errorCode |= uploadInfo->printPage();

    AbstractView *setFilePathPage = new ConsoleViewSetFilePathPage{this,input, output};
    errorCode |= setFilePathPage->printPage();

    model->setFilePath(enteredData);


    AbstractView *setFileLifetime = new ConsoleViewSetFileLifetimePage{this,input, output};
    errorCode |= setFileLifetime->printPage();

    model->setFileLifetime(enteredData);


    AbstractView *setEnteredPasswordPage = new ConsoleViewSetEnteredUsersPasswordPage{this,input, output};
    errorCode |= setEnteredPasswordPage->printPage();

    model->setFilePassword(enteredData);

    networkClient->manageConnection();

    AbstractShowInfoView *infoView = new ConsoleViewExitMessagePage{output};
    infoView->printInfo(model->getExitMessage());

    delete uploadInfo;
    delete setFilePathPage;
    delete setFileLifetime;
    delete setEnteredPasswordPage;
    delete infoView;

    return errorCode;
}
