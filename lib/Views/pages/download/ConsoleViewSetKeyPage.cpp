#include "view_presenter.h"

int  ConsoleViewSetKeyPage::printPage() {

    std::string key{};
    isValidKey<std::string> isValidKey{};
    int errorCode = INIT_VALUE;

    do {
        if (errorCode != SUCCESS) {
            errorView->keyFileErrorPrint(output, errorCode);
        }

        output << std::endl << "Key: ";
        input >> key;

        errorCode = isValidKey(key);

    } while (errorCode != SUCCESS);

    presenter->setEnteredData(key);
    return SUCCESS;
}
