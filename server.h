#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <cstring>          // Include c string functions
#include <iostream>         // Include input/output operations
#include <netinet/in.h>     // Include structures for the internet domain address
#include <sys/socket.h>     // Include socket functions
#include <unistd.h>         // Include standard symbolic constants and types
#include <thread>
#include <vector>
#include <mutex>

class Server;

using SharedPointerOfServer = std::shared_ptr<Server>;

class Server
{
    private:
    std::vector<int> clientSockets;
    int serverSocket;
    sockaddr_in serverAddress;
    std::mutex mt;

    static SharedPointerOfServer onlyObject;
    Server() = default;

    Server(const Server&) = delete;
    Server(Server&&) = delete;

    Server& operator=(const Server&) = delete;
    Server& operator=(Server&&) = delete;

    public:
    ~Server();
    static SharedPointerOfServer GetInstance();

    void start();

};

#endif // SERVER_H