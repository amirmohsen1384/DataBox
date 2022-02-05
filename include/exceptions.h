#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
class AbstractException
{
public:
    virtual void showMessage() const;
};
class WriteFailedException : public AbstractException
{
public:
    void showMessage() const override;
};
class OpenFailedException : public AbstractException
{
public:
    void showMessage() const override;
};
class UnsupportedFormatException : public AbstractException
{
public:
    void showMessage() const override;
};
class CorruptFileException : public AbstractException
{
public:
    void showMessage() const override;
};
#endif // EXCEPTIONS_H
