#ifndef MESSAGEFAILEDEXCEPTION_H
#define MESSAGEFAILEDEXCEPTION_H

#include <future>
#include <string>

class MessageFailedException : public std::future_error
{
    private: 
    std::string _message{""};

    public:
    MessageFailedException() = delete;
    ~MessageFailedException() = default;

    MessageFailedException& operator=(const MessageFailedException&) = delete;
    MessageFailedException(const MessageFailedException&) = delete;

    MessageFailedException(MessageFailedException&&) = delete;
    MessageFailedException& operator=(MessageFailedException&&) = delete;

    MessageFailedException(std::string _message, std::future_errc ec) : _message{_message}, std::future_error{ec}{};

    std::string message() const { return _message; }
};



#endif // MESSAGERECEIVEFAILEDEXCEPTION_H
