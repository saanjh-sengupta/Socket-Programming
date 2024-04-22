#ifndef CLIENT_H
#define CLIENT_H

#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <mutex>
// #include <arpa/inet.h>

class Client
{
    private:
    int clientSocket;
    sockaddr_in serverAddress;
    std::string message{""};
    std::mutex mt;

    public:
    Client(const std::string& message);
    Client() = delete;
    ~Client();

    Client(const Client&) = default;
    Client(Client&&) = delete;

    Client& operator=(const Client&) = default;
    Client& operator=(Client&&) = delete;

    void start();
};

#endif // CLIENT_H