#ifndef CLIENTCONNECTIONFAILEDEXCEPTION_H
#define CLIENTCONNECTIONFAILEDEXCEPTION_H

#include <future>
#include <string>

class ClientConnectionFailedException : public std::future_error
{
    private: 
    std::string _message{""};

    public:
    ClientConnectionFailedException() = delete;
    ~ClientConnectionFailedException() = default;

    ClientConnectionFailedException& operator=(const ClientConnectionFailedException&) = delete;
    ClientConnectionFailedException(const ClientConnectionFailedException&) = delete;

    ClientConnectionFailedException(ClientConnectionFailedException&&) = delete;
    ClientConnectionFailedException& operator=(ClientConnectionFailedException&&) = delete;

    ClientConnectionFailedException(std::string _message, std::future_errc ec) : _message{_message}, std::future_error{ec}{};

    std::string message() const { return _message; }
};

#endif // CLIENTCONNECTIONFAILEDEXCEPTION_H
