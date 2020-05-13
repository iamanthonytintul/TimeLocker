#include <iostream>
#include "view_presenter.h"

using std::ostream;
using std::endl;

int ConsoleErrorView::filePasswordErrorPrint(ostream &output, int errorCode) {
    switch (errorCode) {
        case NO_DATA_WAS_READ:
            output << "You should enter the password" << endl;
            break;
        case TOO_SHORT_PASSWORD:
            output << "You entered too short password" << endl;
            break;
        case TOO_LONG_PASSWORD:
            output << "You entered too long password" << endl;
            break;
        default:
            output << "Please follow the given instructure" << endl;
    }
    output << "Please try again" << endl;

    return SUCCESS;
}

int ConsoleErrorView::filePathErrorPrint(ostream &output, int errorCode) {
    switch (errorCode) {
        case NO_DATA_WAS_READ:
            output << "You should enter the file path" << endl;
            break;
        case NO_SUCH_FILE_IN_DIRECTORY:
            output << "No such file in the directory" << endl;
            break;
        default:
            output << "Please follow the given instructure" << endl;
    }
    output << "Try again" << endl;

    return SUCCESS;
}

int ConsoleErrorView::fileLifeTimeErrorPrint(ostream &output, int errorCode) {
    switch (errorCode) {
        case NO_DATA_WAS_READ:
            output << "Please enter the file lifetime" << endl;
            break;
        case OUT_OF_BORDER_LIFETIME:
        case NOT_LIFETIME_VALUE:
            output << "Please enter a number within the given borders" << endl;
            break;
        default:
            output << "Please follow the given instructure" << endl;
    }

    return SUCCESS;
}


int ConsoleErrorView::applicationModeErrorPrint(ostream &output, int errorCode) {
    switch (errorCode) {
        case NO_DATA_WAS_READ:
            output << "Please enter the mode" << endl;
            break;
        case OUT_OF_BORDER_MODE:
        case NOT_MODE_VALUE:
            output << "Please choose a proposed mode" << endl;
            break;
        default:
            output << "Please follow the given instructure" << endl;
    }
    output << "Try again" << endl;

    return SUCCESS;
}


int ConsoleErrorView::keyFileErrorPrint(ostream &output, int errorCode) {
    switch (errorCode) {
        case NO_DATA_WAS_READ:
            output << "Please enter the key" << endl;
            break;
        case OUT_OF_BORDER_MODE:
        case NOT_MODE_VALUE:
            output << "Please enter a key with length within the given borders" << endl;
            break;
        default:
            output << "Please follow the given instructure" << endl;
    }
    output << "Try again" << endl;

    return SUCCESS;
}


