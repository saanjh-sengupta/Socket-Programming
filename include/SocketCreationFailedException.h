#ifndef SOCKETCREATIONFAILEDEXCEPTION_H
#define SOCKETCREATIONFAILEDEXCEPTION_H

#include <future>
#include <string>

class SocketCreationFailedException : public std::future_error
{
    private: 
    std::string _message{""};

    public:
    SocketCreationFailedException() = delete;
    ~SocketCreationFailedException() = default;

    SocketCreationFailedException& operator=(const SocketCreationFailedException&) = delete;
    SocketCreationFailedException(const SocketCreationFailedException&) = delete;

    SocketCreationFailedException(SocketCreationFailedException&&) = delete;
    SocketCreationFailedException& operator=(SocketCreationFailedException&&) = delete;

    SocketCreationFailedException(std::string _message, std::future_errc ec) : _message{_message}, std::future_error{ec}{};

    std::string message() const { return _message; }
};

#endif // SOCKETCREATIONFAILEDEXCEPTION_H
