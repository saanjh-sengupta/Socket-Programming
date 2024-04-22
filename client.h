#ifndef CLIENT_H
#define CLIENT_H

#include <memory>           // For usage of smart pointers
#include <cstring>          // Include c string functions
#include <iostream>         // Include input/output operations
#include <netinet/in.h>     // Include structures for the internet domain address
#include <sys/socket.h>     // Include socket functions
#include <unistd.h>         // Include standard symbolic constants and types
#include <thread>           // To implement concurrency
#include <mutex>            // To lock critical sections while performing threading
// #include <arpa/inet.h>

// All custom exception files listed below
#include "SocketCreationFailedException.h"
#include "ClientConnectionFailedException.h"
#include "MessageFailedException.h"
#include "BindFailedException.h"
#include "ListenFailedException.h"

class Client    
{
    private:
    // Private data members of the client class
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