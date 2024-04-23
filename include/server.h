#ifndef SERVER_H
#define SERVER_H

#include <memory>                                        // For usage of smart pointers
#include <cstring>                                       // Include c string functions
#include <iostream>                                      // Include input/output operations
#include <netinet/in.h>                                  // Include structures for the internet domain address
#include <sys/socket.h>                                  // Include socket functions
#include <unistd.h>                                      // Include standard symbolic constants and types
#include <thread>                                        // To implement concurrency
#include <list>                                          // To store client sockets (for multiple client and single server interaction)
#include <mutex>                                         // To lock critical sections while performing threading

// All the custom exception files listed below
#include "SocketCreationFailedException.h"              
#include "ClientConnectionFailedException.h"
#include "MessageFailedException.h"
#include "BindFailedException.h"
#include "ListenFailedException.h"

class Server;               // Forward declaration of the Server Class           

// Alias for a unique pointer of server class
using UniquePointerOfServer = std::unique_ptr<Server>;

class Server
{
    private:
    // Private data member of Server class
    std::list<int> clientSockets; 
    int serverSocket;
    sockaddr_in serverAddress;
    std::mutex mt;

    static UniquePointerOfServer onlyObject;
    Server() = default;

    Server(const Server&) = delete;
    Server(Server&&) = delete;

    Server& operator=(const Server&) = delete;
    Server& operator=(Server&&) = delete;

    public:
    ~Server();
    static UniquePointerOfServer& GetInstance();

    void start(int noOfTotalClients);

};

#endif // SERVER_H