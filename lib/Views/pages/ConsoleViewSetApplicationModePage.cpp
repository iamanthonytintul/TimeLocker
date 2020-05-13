#include "view_presenter.h"

int ConsoleViewSetApplicationModePage::printPage() {

    int errorCode = INIT_VALUE;
    string mode;
    isValidApplicationMode<int> isValidApplicationMode;

    do {
        if (errorCode != SUCCESS) {
            errorView->applicationModeErrorPrint(output, errorCode);
        }

        output << std::endl << "Enter '" << UPLOAD_MODE << "' to upload your file and '"<< DOWNLOAD_MODE << "' to download your file: ";
        input >> mode;

        errorCode = isValidApplicationMode(mode);

    } while (errorCode != SUCCESS);

    presenter->setEnteredData(mode);

    return SUCCESS;
}