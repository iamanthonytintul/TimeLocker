#include "view_presenter.h"

int ConsoleViewUploadFileMessagePage::printPage() {
    output << std::endl << "For the security of storing your data, you must create a password. Follow the instructions below."
           << std::endl << std::endl;
    output << "There are two options for the password:" << std::endl << std::endl;
    output << "Your own password. " << MIN_PASSWORD_LENGTH << " <= Length <= " << MAX_PASSWORD_LENGTH << std::endl;
    output << "Automatically generated, easy to remember password. " << MIN_PASSWORD_LENGTH << " <= Length <= "
           << MAX_PASSWORD_LENGTH << " with letters only" << std::endl << std::endl;

    return SUCCESS;
}
