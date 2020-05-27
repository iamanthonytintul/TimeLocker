#include "View.h"

int ConsoleViewExitMessagePage::printInfo(const std::string &message) {
    output << std::endl << message << std::endl;
    output << std::endl << "Hope to see you soon" << std::endl;

    return SUCCESS;
}