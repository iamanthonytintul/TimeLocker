#include "view_presenter.h"

int ConsoleViewSetEnteredUsersPasswordPage::printPage() {

    int errorCode = SUCCESS;
    string enteredPassword{""};
    string reenteredPassword{""};
    isValidFilePassword<int> isValidFilePassword;

    do {

        if (errorCode != SUCCESS) {
            errorView->filePasswordErrorPrint(output, errorCode);
        } else if (enteredPassword != reenteredPassword) {
            output << "Password Mismatch" << std::endl;
        }

        output << std::endl << "Set the password for the file here." << std::endl;

        output << std::endl << "New password: ";
        input >> enteredPassword;

        output << std::endl << "Re-enter password: ";
        input >> reenteredPassword;

        errorCode = isValidFilePassword(enteredPassword);

    } while (errorCode != SUCCESS || enteredPassword != reenteredPassword);

    presenter->setEnteredData(enteredPassword);

    return SUCCESS;

}
