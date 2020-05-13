#include "view_presenter.h"

int  ConsoleViewSetPasswordPage::printPage() {
    int errCode = INIT_VALUE;
    string password;
    isValidFilePassword<int> isValidFilePassword;

    do {
        if (errCode != SUCCESS) {
            errorView->filePasswordErrorPrint(output, errCode);
        }
        output << std::endl << "The password to your file: ";

        input >> password;

        errCode = isValidFilePassword(password);
    } while (errCode != SUCCESS);

    presenter->setEnteredData(password);

    return SUCCESS;
}
