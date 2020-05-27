#include <iostream>

namespace constants {
    const std::string DOWNLOAD_PATH = "/uploads/";
    const std::string ACCEPTABLE_MIME = "application/zip";
    const std::string MIME_REGEX = ".*\\.zip";
    const std::string FILE_TYPE = ".zip";
    const std::string TIMEHEADER = "HTTP_FILE_LIFETIME";
    const std::string PASSHEADER = "HTTP_FILE_PASSWORD";
    const std::string FILEKEY = "File-Key";
    const std::string AUTHHEADER = "HTTP_AUTHORIZATION";
    const std::string KEYMAP = "Key";
    const std::string PASSMAP = "Password";
    const int MIN_LIMIT = 0;
    const int MAX_LIMIT = 50*1024*1024;
    const char DELIMETER_KEY = ':';
    const int DEFAULT_TIME = 1;
    const int FAIL = 0;
    const int SUCCESS = 1;
    const int BAD_REQUEST = 400;
    const int NOT_FOUND = 404;
    const int SUCCESSFUL = 200;
    const int METHOD_NOT_ALLOWED = 405;
}