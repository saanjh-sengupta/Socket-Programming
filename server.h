#ifndef SERVER_H
#define SERVER_H

#include <cstring>          // Include c string functions
#include <iostream>         // Include input/output operations
#include <netinet/in.h>     // Include structures for the internet domain address
#include <sys/socket.h>     // Include socket functions
#include <unistd.h>         // Include standard symbolic constants and types
#include <thread>

class Server
{
    private:
    int serverSocket;
    int clientSocket;
    sockaddr_in serverAddress;

    public:
    Server() = default;
    ~Server();

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    Server(Server&&) = delete;
    Server& operator=(Server&&) = delete;

    void start();
};

#endif // SERVER_H