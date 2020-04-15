template <class Type>
class IDownloadManager {
public:
    virtual Type DownloadData(int) = 0;
    virtual ~IDownloadManager() = default;
};

class IUploadManager {
public:
    virtual int UploadData() = 0;
    virtual ~IUploadManager() = default;
};

class IConnectManager {
public:
    virtual int Connect() = 0;
    virtual int CloseConnect() = 0;

    virtual ~IConnectManager() = default;
};