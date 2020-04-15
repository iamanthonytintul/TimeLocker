template<class Type>
class IClient {
public:
    virtual int Connect() = 0;
    virtual int Send() = 0;
    virtual Type Receive() = 0;
    virtual ~IClient() = default;
};

template <class Type>
class IReader{
public:
    virtual int read(FILE*, Type*, int) = 0;
    virtual bool isValidRead(Type *) = 0;
    virtual ~IReader() = default;
};
