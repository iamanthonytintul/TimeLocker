#include <iostream>
#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <filesystem>
#include "Checkers.hpp"
#include "Model.h"
#include "Network.h"
#include "Presenter.h"

class AbstractView {
public:
    virtual int printPage() = 0;

    virtual ~AbstractView() = default;
};

class AbstractShowInfoView {
public:
    virtual int printInfo(const std::string &message) = 0;

    virtual ~AbstractShowInfoView() = default;
};

class ConsoleErrorView {
public:
    ConsoleErrorView() = default;

    int filePasswordErrorPrint(std::ostream &output, int errorCode);

    int filePathErrorPrint(std::ostream &output, int errorCode);

    int fileLifeTimeErrorPrint(std::ostream &output, int errorCode);

    int applicationModeErrorPrint(std::ostream &output, int errorCode);

    int fileKeyErrorPrint(std::ostream &output, int errorCode);

};

class ConsoleViewUploadFileMessagePage : public AbstractView {
public:
    ConsoleViewUploadFileMessagePage(AbstractApplicationPresenter *applicationPresenter, std::istream &cin_ = std::cin,
                                     std::ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                                        presenter(applicationPresenter) {}

    int printPage() override;

private:
    AbstractApplicationPresenter *presenter;
    std::istream &input;
    std::ostream &output;
};

class ConsoleViewSetApplicationModePage : public AbstractView {
public:
    ConsoleViewSetApplicationModePage(AbstractApplicationPresenter *applicationPresenter, std::istream &cin_ = std::cin,
                                      std::ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                                         presenter(applicationPresenter) {}

    int printPage() override;

private:
    AbstractApplicationPresenter *presenter;
    ConsoleErrorView errorView;
    std::istream &input;
    std::ostream &output;
};

class ConsoleViewSetEnteredUsersPasswordPage : public AbstractView {
public:
    ConsoleViewSetEnteredUsersPasswordPage(AbstractApplicationPresenter *applicationPresenter,
                                           std::istream &cin_ = std::cin,
                                           std::ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                                              presenter(applicationPresenter) {}

    int printPage() override;

private:
    AbstractApplicationPresenter *presenter;
    ConsoleErrorView errorView;
    std::istream &input;
    std::ostream &output;
};

class ConsoleViewSetFileLifetimePage : public AbstractView {
public:
    ConsoleViewSetFileLifetimePage(AbstractApplicationPresenter *applicationPresenter, std::istream &cin_ = std::cin,
                                   std::ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                                      presenter(applicationPresenter) {}

    int printPage() override;

private:
    AbstractApplicationPresenter *presenter;
    ConsoleErrorView errorView;
    std::istream &input;
    std::ostream &output;
};

class ConsoleViewDownloadFileMessagePage : public AbstractView {
public:
    ConsoleViewDownloadFileMessagePage(AbstractApplicationPresenter *applicationPresenter,
                                       std::istream &cin_ = std::cin,
                                       std::ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                                          presenter(applicationPresenter) {}

    int printPage() override;

private:
    AbstractApplicationPresenter *presenter;
    std::istream &input;
    std::ostream &output;
};

class ConsoleViewSetKeyPage : public AbstractView {
public:
    explicit ConsoleViewSetKeyPage(AbstractApplicationPresenter *applicationPresenter, std::istream &cin_ = std::cin,
                                   std::ostream &cout_ = std::cout) : presenter(applicationPresenter), input(cin_),
                                                                      output(cout_) {}

    int printPage() override;

private:
    AbstractApplicationPresenter *presenter;
    ConsoleErrorView errorView;
    std::istream &input;
    std::ostream &output;
};

class ConsoleViewSetPasswordPage : public AbstractView {
public:
    explicit ConsoleViewSetPasswordPage(AbstractApplicationPresenter *applicationPresenter,
                                        std::istream &cin_ = std::cin,
                                        std::ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                                           presenter(applicationPresenter) {}

    int printPage() override;

private:
    AbstractApplicationPresenter *presenter;
    ConsoleErrorView errorView;
    std::istream &input;
    std::ostream &output;
};

class ConsoleViewStartPage : public AbstractView {
public:
    ConsoleViewStartPage(AbstractApplicationPresenter *applicationPresenter, std::istream &cin_ = std::cin,
                         std::ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                            presenter(applicationPresenter) {}

    int printPage() override;

private:
    AbstractApplicationPresenter *presenter;
    std::istream &input;
    std::ostream &output;
};

class ConsoleViewSetFilePathPage : public AbstractView {

public:
    ConsoleViewSetFilePathPage(AbstractApplicationPresenter *applicationPresenter, std::istream &cin_ = std::cin,
                               std::ostream &cout_ = std::cout) : input(cin_), output(cout_),
                                                                  presenter(applicationPresenter) {}

    int printPage() override;

private:
    AbstractApplicationPresenter *presenter;
    ConsoleErrorView errorView;
    std::istream &input;
    std::ostream &output;
};

class ConsoleViewExitMessagePage : public AbstractShowInfoView {
public:

    ConsoleViewExitMessagePage(std::ostream &cout_ = std::cout) : output(cout_) {}

    int printInfo(const std::string &message) override;

private:
    std::ostream &output;
};

class ConsolePasswordReader {
public:
    ConsolePasswordReader() = default;

    std::string readPassword(std::istream &input = std::cin, std::ostream &output = std::cout);

private:
    std::string password;
};