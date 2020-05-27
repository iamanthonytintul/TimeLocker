#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

const int FIRST_SYMBOL = 0;

const int INIT_VALUE = 0;
const int SUCCESS = 0;
const int NO_DATA_WAS_READ = 1;

const char DOWNLOAD_MODE = 'd';
const char UPLOAD_MODE = 'u';
const int MAX_MODE_LENGTH = 1;

const int MAX_KEY_LENGTH = 32;

enum PASSWORD_ERROR {
    TOO_SHORT_PASSWORD = 2, TOO_LONG_PASSWORD
};
enum FILE_PATH_ERROR {
    NO_SUCH_FILE_IN_DIRECTORY = 2
};
enum FILE_LIFETIME_ERROR {
    OUT_OF_BORDER_LIFETIME = 2, NOT_LIFETIME_VALUE
};
enum MODE_ERROR {
    NOT_MODE_VALUE = 2, OUT_OF_BORDER_MODE
};
enum KEY_ERROR {
    NOT_KEY_VALUE = 2, OUT_SIZE_OF_KEY
};


const int MIN_PASSWORD_LENGTH = 8;
const int MAX_PASSWORD_LENGTH = 32;

const int MIN_FILE_LIFETIME_DAYS = 1;
const int MAX_FILE_LIFETIME_DAYS = 7;
const int MAX_FILE_LIFETIME_LENGTH = 2;

using std::istream;
using std::ifstream;
using std::istringstream;
using std::string;

//---------------------------------------------------------------------------------

template<class ReadingType>
class isValidFilePath {
public:
    isValidFilePath() = default;

    int operator()(string &readData);
};

template<class ReadingType>
int isValidFilePath<ReadingType>::operator()(string &readData) {
    if (readData.empty()) {
        return NO_DATA_WAS_READ;
    }
    ifstream tmp;
    tmp.open(readData);
    if (!tmp.is_open()) {
        return NO_SUCH_FILE_IN_DIRECTORY;
    }
    return SUCCESS;
}

//---------------------------------------------------------------------------------

template<class ReadingType>
class isValidFilePassword {
public:
    isValidFilePassword() = default;

    int operator()(string &readData);
};

template<class ReadingType>
int isValidFilePassword<ReadingType>::operator()(string &readData) {
    if (readData.empty()) {
        return NO_DATA_WAS_READ;
    }
    if (readData.length() <= MIN_PASSWORD_LENGTH) {
        return TOO_SHORT_PASSWORD;
    }
    if (readData.length() >= MAX_PASSWORD_LENGTH) {
        return TOO_LONG_PASSWORD;
    }
    return SUCCESS;
}

//---------------------------------------------------------------------------------

template<class ReadingType>
class isValidFileLifetime {
public:
    isValidFileLifetime() = default;

    int operator()(string &readData);
};

template<class ReadingType>
int isValidFileLifetime<ReadingType>::operator()(string &readData) {

    if (readData.empty()) {
        return NO_DATA_WAS_READ;
    }
    if (readData.length() > MAX_FILE_LIFETIME_LENGTH) {
        return OUT_OF_BORDER_LIFETIME;
    }

    bool isError = false;

    for (int i = 0; i < readData.length() && !isError; i++) {
        if (readData[i] < '0' || readData[i] > '9') {
            isError = true;
        }
    }
    if (isError) {
        return NOT_LIFETIME_VALUE;
    }

    ReadingType lifetime = INIT_VALUE;
    istringstream basicIstringstream(readData);
    basicIstringstream >> lifetime;

    if (lifetime < MIN_FILE_LIFETIME_DAYS || lifetime > MAX_FILE_LIFETIME_DAYS) {
        return OUT_OF_BORDER_LIFETIME;
    }

    return SUCCESS;
}

//---------------------------------------------------------------------------------

template<class ReadingType>
class isValidApplicationMode {
public:
    isValidApplicationMode() = default;

    int operator()(string &readData);
};

template<class ReadingType>
int isValidApplicationMode<ReadingType>::operator()(string &readData) {
    if (readData.empty()) {
        return NO_DATA_WAS_READ;
    }
    if (readData.length() > MAX_MODE_LENGTH) {
        return OUT_OF_BORDER_MODE;
    }

    bool isError = false;

    for (int i = 0; i < readData.length() && !isError; i++) {
        if (readData[i] != DOWNLOAD_MODE && readData[i] != UPLOAD_MODE) {
            isError = true;
        }
    }
    if (isError) {
        return NOT_MODE_VALUE;
    }

    return SUCCESS;
}

//---------------------------------------------------------------------------------

template<class ReadingType>
class isValidKey {
public:
    isValidKey() = default;

    int operator()(string &readData);
};

template<class ReadingType>
int isValidKey<ReadingType>::operator()(string &readData) {
    if (readData.empty()) {
        return NO_DATA_WAS_READ;
    }
    if (readData.length() != MAX_KEY_LENGTH) {
        return OUT_SIZE_OF_KEY;
    }

    bool isError = false;

    for (int i = 0; i < readData.length() && !isError; i++) {
        if (readData[i] < 'a' || readData[i] > 'z') {
            isError = true;
        }
    }
    if (isError) {
        return NOT_KEY_VALUE;
    }

    return SUCCESS;
}

//---------------------------------------------------------------------------------