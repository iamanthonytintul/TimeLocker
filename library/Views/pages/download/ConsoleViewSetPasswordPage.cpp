#include "View.h"

int  ConsoleViewSetPasswordPage::printPage() {
    int errCode = INIT_VALUE;
    std::string password;
    isValidFilePassword<int> isValidFilePassword;
    input.ignore();

    auto* consolePasswordReader = new ConsolePasswordReader{};
    do {
        if (errCode != SUCCESS) {
            errorView.filePasswordErrorPrint(output, errCode);
        }
        output << std::endl << "The password to your file: ";

        password = consolePasswordReader->readPassword(input, output);

        errCode = isValidFilePassword(password);
    } while (errCode != SUCCESS);

    presenter->setEnteredData(password);

    delete consolePasswordReader;
    return SUCCESS;
}
