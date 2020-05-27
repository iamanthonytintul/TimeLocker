#include "View.h"

int ConsoleViewUploadFileMessagePage::printPage() {
    output << std::endl
           << "For the security of storing your data, you must create a password. Follow the instructions below."
           << std::endl;
    output << std::endl
           << "Your own password. " << MIN_PASSWORD_LENGTH << " <= Length <= " << MAX_PASSWORD_LENGTH
           << std::endl;
    return SUCCESS;
}
