#include "view_presenter.h"

int ApplicationPresenter::start() {
    AbstractView *startPage = new ConsoleViewStartPage{this};

    startPage->printPage();

    int errorCode = setApplicationMode();

    delete startPage;
    return errorCode;
}

int ApplicationPresenter::setApplicationMode() {
    AbstractView *appModePage = new ConsoleViewSetApplicationModePage{this};

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

    AbstractView *downloadInfo = new ConsoleViewDownloadFileMessagePage{this};
    errorCode |= downloadInfo->printPage();

    AbstractView *setKeyPage = new ConsoleViewSetKeyPage{this};
    errorCode |= setKeyPage->printPage();

    model->setFileKey(enteredData);

    AbstractView *setPasswordPage = new ConsoleViewSetPasswordPage{this};
    errorCode |= setPasswordPage->printPage();

    model->setFilePassword(enteredData);

    //TODO: Подключение к серверу

    delete downloadInfo;
    delete setKeyPage;
    delete setPasswordPage;

    return errorCode;
}

int ApplicationPresenter::setEnteredData(std::string &data) {

    enteredData = data;
    return SUCCESS;
}

int ApplicationPresenter::setUploadInfo() {

    int errorCode = SUCCESS;

    AbstractView *uploadInfo = new ConsoleViewUploadFileMessagePage{this};
    errorCode |= uploadInfo->printPage();

    AbstractView *setFilePathPage = new ConsoleViewSetFilePathPage{this};
    errorCode |= setFilePathPage->printPage();

    model->setFilePath(enteredData);


    AbstractView *setFileLifetime = new ConsoleViewSetFileLifetimePage{this};
    errorCode |= setFileLifetime->printPage();

    model->setFileLifetime(enteredData);


    AbstractView *setEnteredPasswordPage = new ConsoleViewSetEnteredUsersPasswordPage{this};
    errorCode |= setEnteredPasswordPage->printPage();

    model->setFilePassword(enteredData);

    //TODO: Подключение к серверу

    delete uploadInfo;
    delete setFilePathPage;
    delete setFileLifetime;
    delete setEnteredPasswordPage;

    return errorCode;
}
