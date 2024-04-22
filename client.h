#ifndef CLIENT_H
#define CLIENT_H

#include <cstring>          // Include c string functions
#include <iostream>         // Include input/output operations
#include <netinet/in.h>     // Include structures for the internet domain address
#include <sys/socket.h>     // Include socket functions
#include <unistd.h>         // Include standard symbolic constants and types
#include <thread>

class Client
{
    private:
    int clientSocket;
    sockaddr_in serverAddress;

    public:
    Client() = default;
    ~Client();

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;

    void start();
};

#endif // CLIENT_H