#ifndef LISTENFAILEDEXCEPTION_H
#define LISTENFAILEDEXCEPTION_H

#include <future>
#include <string>

class ListenFailedException : public std::future_error
{
    private: 
    std::string _message{""};

    public:
    ListenFailedException() = delete;
    ~ListenFailedException() = default;

    ListenFailedException& operator=(const ListenFailedException&) = delete;
    ListenFailedException(const ListenFailedException&) = delete;

    ListenFailedException(ListenFailedException&&) = delete;
    ListenFailedException& operator=(ListenFailedException&&) = delete;

    ListenFailedException(std::string _message, std::future_errc ec) : _message{_message}, std::future_error{ec}{};

    std::string message() const { return _message; }
};

#endif // LISTENFAILEDEXCEPTION_H
