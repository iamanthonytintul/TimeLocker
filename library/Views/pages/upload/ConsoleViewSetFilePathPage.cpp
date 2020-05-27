#include "View.h"

int  ConsoleViewSetFilePathPage::printPage() {
    int errorCode = INIT_VALUE;
    string enteredFilePath;
    isValidFilePath<string> isValidFilePath;


    do {
        if (errorCode != SUCCESS) {
            errorView.filePathErrorPrint(output, errorCode);
        }

        output << std::endl << "Set the path to your file here: ";

        input >> enteredFilePath;

        errorCode = isValidFilePath(enteredFilePath);

    } while (errorCode != SUCCESS);

    presenter->setEnteredData(enteredFilePath);

    return SUCCESS;
}
