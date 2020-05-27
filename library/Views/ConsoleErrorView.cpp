#include <iostream>
#include "View.h"

int ConsoleErrorView::filePasswordErrorPrint(std::ostream &output, int errorCode) {
    switch (errorCode) {
        case NO_DATA_WAS_READ:
            output << "You should enter the password" << std::endl;
            break;
        case TOO_SHORT_PASSWORD:
            output << "You entered too short password" << std::endl;
            break;
        case TOO_LONG_PASSWORD:
            output << "You entered too long password" << std::endl;
            break;
        default:
            output << "Please follow the given instruction" << std::endl;
    }
    output << "Please try again" << std::endl;

    return SUCCESS;
}

int ConsoleErrorView::filePathErrorPrint(std::ostream &output, int errorCode) {
    switch (errorCode) {
        case NO_DATA_WAS_READ:
            output << "You should enter the file path" << std::endl;
            break;
        case NO_SUCH_FILE_IN_DIRECTORY:
            output << "No such file in the directory" << std::endl;
            break;
        default:
            output << "Please follow the given instruction" << std::endl;
    }
    output << "Try again" << std::endl;

    return SUCCESS;
}

int ConsoleErrorView::fileLifeTimeErrorPrint(std::ostream &output, int errorCode) {
    switch (errorCode) {
        case NO_DATA_WAS_READ:
            output << "Please enter the file lifetime" << std::endl;
            break;
        case OUT_OF_BORDER_LIFETIME:
        case NOT_LIFETIME_VALUE:
            output << "Please enter a number within the given borders" << std::endl;
            break;
        default:
            output << "Please follow the given instruction" << std::endl;
    }

    return SUCCESS;
}

int ConsoleErrorView::applicationModeErrorPrint(std::ostream &output, int errorCode) {
    switch (errorCode) {
        case NO_DATA_WAS_READ:
            output << "Please enter the mode" << std::endl;
            break;
        case OUT_OF_BORDER_MODE:
        case NOT_MODE_VALUE:
            output << "Please choose a proposed mode" << std::endl;
            break;
        default:
            output << "Please follow the given instruction" << std::endl;
    }
    output << "Try again" << std::endl;

    return SUCCESS;
}

int ConsoleErrorView::fileKeyErrorPrint(std::ostream &output, int errorCode) {
    switch (errorCode) {
        case NO_DATA_WAS_READ:
            output << "Please enter the key" << std::endl;
            break;
        case OUT_SIZE_OF_KEY:
            output << "Please enter a key with length = " << MAX_KEY_LENGTH << std::endl;
            break;
        case NOT_KEY_VALUE:
            output << "Please enter correct key" << std::endl;
            break;
        default:
            output << "Please follow the given instruction" << std::endl;
    }
    output << "Try again" << std::endl;

    return SUCCESS;
}

