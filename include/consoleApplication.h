#include "Client.h"
#include "Managers.h"

#define SUCCESS 0
#define BUFF_SIZE 80
enum { INVALID_PATH = 1, NO_SUCH_FILE };
enum { TOO_LONG_PASSWORD };
enum { DOWNLOAD_EVENT = 1, UPLOAD_EVENT};

template<class Type>
class PasswordReader : public IReader<Type> {
public:
    int read(FILE*, Type*, int) override;
    bool isValidRead(Type*) override;
};

template<class Type>
int PasswordReader<Type>::read(FILE* input, Type* buff, int buffSize) {
    return NO_SUCH_FILE;
}

template<class Type>
bool PasswordReader<Type>::isValidRead(Type*) {
    return false;
}

template<class Type>
class FilePathReader : public IReader<Type> {
public:
    int read(FILE*, Type*, int) override;
    bool isValidRead(Type*) override;
};

template<class Type>
int FilePathReader<Type>::read(FILE* input, Type* buff, int buffSize) {
    return NO_SUCH_FILE;
}

template<class Type>
bool FilePathReader<Type>::isValidRead(Type*) {
    return false;
}

template<class Type>
class ServerDownload : public IDownloadManager<Type> {
public:
    Type DownloadData(int) override;
};
template<class Type>
Type ServerDownload<Type>::DownloadData(int) {
    return nullptr;
}

class ServerUpload : public IUploadManager {
public:
    int UploadData() override;
};

class ServerConnection : public IConnectManager {
public:
    int Connect() override;

    int CloseConnect() override;
};

template<class Type>
class ConsoleClient : public IClient<Type> {

private:

    int socketDescriptor;
    IConnectManager *connectManager;
    IUploadManager *uploadManager;
    IDownloadManager<Type> *downloadManager;

public:

    int Connect() override;

    int Send() override;

    Type Receive() override;

};

class ArgumentHandler {
private:
    char** arguments;
    int argumentsCount;
    int eventID;
public:
    ArgumentHandler(int, char**);

    bool setEventID();

    int getEventID();

};


