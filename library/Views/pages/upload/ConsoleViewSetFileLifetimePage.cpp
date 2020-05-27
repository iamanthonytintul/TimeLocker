#include "View.h"

int  ConsoleViewSetFileLifetimePage::printPage() {
    int errorCode = INIT_VALUE;

    string enteredLifetime;
    isValidFileLifetime<int> isValidFileLifetime;

    do {

        if (errorCode != SUCCESS) {
            errorView.fileLifeTimeErrorPrint(output, errorCode);
        }

        output << std::endl << "Please set the lifetime for the file ( 1 - " << MAX_FILE_LIFETIME_DAYS << " days ): ";

        input >> enteredLifetime;
        errorCode = isValidFileLifetime(enteredLifetime);

    } while (errorCode != SUCCESS);

    presenter->setEnteredData(enteredLifetime);

    return SUCCESS;

}
