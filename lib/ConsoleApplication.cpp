#include "consoleApplication.h"

int ServerUpload::UploadData() {
    return 0;
}

int ServerConnection::Connect() {
    return 0;
}

int ServerConnection::CloseConnect() {
    return 0;
}

template<class Type>
int ConsoleClient<Type>::Connect() {
    return 0;
}

template<class Type>
int ConsoleClient<Type>::Send() {
    return 0;
}

template<class Type>
Type ConsoleClient<Type>::Receive() {
    return nullptr;
}

ArgumentHandler::ArgumentHandler(int argc, char** argv) {
    arguments = argv;
    argumentsCount = argc;
    eventID = 0;
}

bool ArgumentHandler::setEventID() {
    return false;
}

int ArgumentHandler::getEventID() {
    return 0;
}
