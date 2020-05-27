#include "View.h"

int ConsoleViewSetEnteredUsersPasswordPage::printPage() {

    int errorCode = SUCCESS;
    string enteredPassword;
    string reenteredPassword;
    isValidFilePassword<int> isValidFilePassword;
    auto* consolePasswordReader = new ConsolePasswordReader{};

    input.ignore();
    do {

        if (errorCode != SUCCESS) {
            errorView.filePasswordErrorPrint(output, errorCode);
        } else if (enteredPassword != reenteredPassword) {
            output << "Password Mismatch" << std::endl;
        }

        output << std::endl << "Set the password for the file here." << std::endl;

        output << std::endl << "New password: ";
        enteredPassword = consolePasswordReader->readPassword(input, output);

        output << std::endl << "Re-enter password: ";
        reenteredPassword = consolePasswordReader->readPassword(input, output);

        errorCode = isValidFilePassword(enteredPassword);

    } while (errorCode != SUCCESS || enteredPassword != reenteredPassword);

    presenter->setEnteredData(enteredPassword);

    delete consolePasswordReader;
    return SUCCESS;

}
