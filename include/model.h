#ifndef TLCONSOLEAPPLICATION_MODEL_H
#define TLCONSOLEAPPLICATION_MODEL_H

#include <string>

struct AbstractModel {
public:

    virtual void setFilePassword(const std::string &filePassword) = 0;
    virtual void setFilePath(const std::string &filePath) = 0;
    virtual void setFileKey(const std::string &fileKey) = 0;
    virtual void setFileLifetime(const std::string &fileLifetime) = 0;
    virtual void setApplicationMode(const std::string &appMode) = 0;

    virtual const std::string &getFilePassword() = 0;
    virtual const std::string &getFilePath() = 0;
    virtual const std::string &getFileKey() = 0;
    virtual const std::string &getFileLifetime() = 0;
    virtual const std::string &getApplicationMode() = 0;

    virtual ~AbstractModel() = default;
};

struct Model: public AbstractModel {

public:

    Model() : _applicationMode(""), _filePassword(""), _filePath(""), _fileKey(""), _fileLifetime("") {}

    void setFilePassword(const std::string &filePassword) override;

    void setFilePath(const std::string &filePath) override;

    void setFileKey(const std::string &fileKey) override;

    void setFileLifetime(const std::string &fileLifetime) override;

    void setApplicationMode(const std::string &appMode) override;

    const std::string &getFilePassword() override;

    const std::string &getFilePath() override;

    const std::string &getFileKey() override;

    const std::string &getFileLifetime() override;

    const std::string &getApplicationMode() override;

private:

    std::string _applicationMode;
    std::string _filePassword;
    std::string _filePath;
    std::string _fileKey;
    std::string _fileLifetime;

};

#endif //TLCONSOLEAPPLICATION_MODEL_H
