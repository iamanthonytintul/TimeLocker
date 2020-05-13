//#include "ViewHeaders/view.h"
//
//int ConsoleViewSetPasswordModePage::printPage() {
//
//    int errorCode = INIT_VALUE;
//    string mode;
//    isValidApplicationMode<int> isValidApplicationMode;
//
//    do {
//        if (errorCode != INIT_VALUE) {
//            errorView->applicationModeErrorPrint(output, errorCode);
//        }
//
//        output << "Enter " << DOWNLOAD_MODE << " for your password and " << UPLOAD_MODE
//             << " for our password: ";
//        input >> mode;
//        errorCode = isValidApplicationMode(mode);
//
//    } while (errorCode != INIT_VALUE);
//
//
//    return SUCCESS;
//}
