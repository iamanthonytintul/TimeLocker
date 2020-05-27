#ifndef TLCONSOLEAPPLICATION_PRESENTER_H
#define TLCONSOLEAPPLICATION_PRESENTER_H

class AbstractApplicationPresenter {
public:
    virtual int start() = 0;

    virtual int setApplicationMode() = 0;

    virtual int setDownloadInfo() = 0;

    virtual int setEnteredData(std::string &data) = 0;

    virtual int setUploadInfo() = 0;

    virtual ~AbstractApplicationPresenter() = default;
};

class ApplicationPresenter : public AbstractApplicationPresenter {
public:
    ApplicationPresenter(AbstractModel *abstractModel, AbstractNetworkClient *abstractNetworkClient,
                         std::istream &in = std::cin, std::ostream &out = std::cout) : model(
            abstractModel), networkClient(abstractNetworkClient), input(in), output(out) {}

    int start() override;

    int setApplicationMode() override;

    int setDownloadInfo() override;

    int setEnteredData(std::string &data) override;

    int setUploadInfo() override;

private:
    AbstractModel *model;
    AbstractNetworkClient *networkClient;
    std::string enteredData{};
    std::istream &input;
    std::ostream &output;
};

#endif
