#include <iostream>
#include <vector>
#include "checkers.hpp"
#include <string>
#include "model.h"
#include "boostNetwork.h"


class ApplicationPresenter {
public:
    ApplicationPresenter(AbstractModel *abstractModel) : model(abstractModel) {
    }

    int start();

    int setApplicationMode();

    int setDownloadInfo();

    int setEnteredData(std::string &data);

    int setUploadInfo();

private:
    AbstractModel *model;
    std::string enteredData{};
};

using std::istream;
using std::ostream;

class AbstractView {
public:
    virtual int printPage() = 0;

    virtual ~AbstractView() = default;
};

class ConsoleErrorView {
public:
    ConsoleErrorView() = default;

    int filePasswordErrorPrint(std::ostream &output, int errorCode);

    int filePathErrorPrint(std::ostream &output, int errorCode);

    int fileLifeTimeErrorPrint(std::ostream &output, int errorCode);

    int applicationModeErrorPrint(std::ostream &output, int errorCode);

    int keyFileErrorPrint(std::ostream &output, int errorCode);

};

class ConsoleViewUploadFileMessagePage : public AbstractView {
public:
    ConsoleViewUploadFileMessagePage(ApplicationPresenter *applicationPresenter, istream &cin_ = std::cin,
                                     ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                            presenter(applicationPresenter) {
        errorView = new ConsoleErrorView();
    }

    int printPage() override;

private:
    ApplicationPresenter *presenter;
    ConsoleErrorView *errorView;
    istream &input;
    ostream &output;
};

class ConsoleViewSetApplicationModePage : public AbstractView {
public:
    ConsoleViewSetApplicationModePage(ApplicationPresenter *applicationPresenter, istream &cin_ = std::cin,
                                      ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                                    presenter(applicationPresenter) {
        errorView = new ConsoleErrorView();
    }

    int printPage() override;

private:
    ApplicationPresenter *presenter;
    ConsoleErrorView *errorView;
    istream &input;
    ostream &output;
};

class ConsoleViewSetEnteredUsersPasswordPage : public AbstractView {
public:
    ConsoleViewSetEnteredUsersPasswordPage(ApplicationPresenter *applicationPresenter, istream &cin_ = std::cin,
                                           ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                                         presenter(applicationPresenter) {
        errorView = new ConsoleErrorView();
    }

    int printPage() override;

private:
    ApplicationPresenter *presenter;
    ConsoleErrorView *errorView;
    istream &input;
    ostream &output;
};

class ConsoleViewSetFileLifetimePage : public AbstractView {
public:
    ConsoleViewSetFileLifetimePage(ApplicationPresenter *applicationPresenter, istream &cin_ = std::cin,
                                   ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                                 presenter(applicationPresenter) {
        errorView = new ConsoleErrorView();
    }

    int printPage() override;

private:
    ApplicationPresenter *presenter;
    ConsoleErrorView *errorView;
    istream &input;
    ostream &output;
};

class ConsoleViewDownloadFileMessagePage : public AbstractView {
public:
    ConsoleViewDownloadFileMessagePage(ApplicationPresenter *applicationPresenter, istream &cin_ = std::cin,
                                       ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                                     presenter(applicationPresenter) {
        errorView = new ConsoleErrorView();
    }

    int printPage() override;

private:
    ApplicationPresenter *presenter;
    ConsoleErrorView *errorView;
    istream &input;
    ostream &output;
};

class ConsoleViewSetKeyPage : public AbstractView {
public:
    ConsoleViewSetKeyPage(ApplicationPresenter *applicationPresenter, istream &cin_ = std::cin,
                          ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                        presenter(applicationPresenter) {
        errorView = new ConsoleErrorView();
    }

    int printPage() override;

private:
    ApplicationPresenter *presenter;
    ConsoleErrorView *errorView;
    istream &input;
    ostream &output;
};

class ConsoleViewSetPasswordPage : public AbstractView {
public:
    ConsoleViewSetPasswordPage(ApplicationPresenter *applicationPresenter, istream &cin_ = std::cin,
                               ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                             presenter(applicationPresenter) {
        errorView = new ConsoleErrorView();
    }

    int printPage() override;

private:
    ApplicationPresenter *presenter;
    ConsoleErrorView *errorView;
    istream &input;
    ostream &output;
};

class ConsoleViewStartPage : public AbstractView {
public:
    ConsoleViewStartPage(ApplicationPresenter *applicationPresenter, istream &cin_ = std::cin,
                         ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                       presenter(applicationPresenter) {
        errorView = new ConsoleErrorView();
    }

    int printPage() override;

private:
    ApplicationPresenter *presenter;
    ConsoleErrorView *errorView;
    istream &input;
    ostream &output;
};

class ConsoleViewSetFilePathPage : public AbstractView {
public:
    ConsoleViewSetFilePathPage(ApplicationPresenter *applicationPresenter, istream &cin_ = std::cin,
                               ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                             presenter(applicationPresenter) {
        errorView = new ConsoleErrorView();
    }

    int printPage() override;

private:
    ApplicationPresenter *presenter;
    ConsoleErrorView *errorView;
    istream &input;
    ostream &output;
};