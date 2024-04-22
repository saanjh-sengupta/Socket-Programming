#ifndef BINDFAILEDEXCEPTION_H
#define BINDFAILEDEXCEPTION_H

#include <future>
#include <string>

class BindFailedException : public std::future_error
{
    private: 
    std::string _message{""};

    public:
    BindFailedException() = delete;
    ~BindFailedException() = default;

    BindFailedException& operator=(const BindFailedException&) = delete;
    BindFailedException(const BindFailedException&) = delete;

    BindFailedException(BindFailedException&&) = delete;
    BindFailedException& operator=(BindFailedException&&) = delete;

    BindFailedException(std::string _message, std::future_errc ec) : _message{_message}, std::future_error{ec}{};

    std::string message() const { return _message; }
};

#endif // BINDFAILEDEXCEPTION_H
