#include "server.h"

Server::~Server()
{
    if(clientSocket)
    {
        close(clientSocket);
    }

    if(serverSocket)
    {
        close(serverSocket);
    }
}

void Server::start()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress));
    
    listen(serverSocket, 5);

    clientSocket = accept(serverSocket, nullptr, nullptr);

    char buffer[1024] = {0};

    recv(clientSocket, buffer, sizeof(buffer), 0);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Message from client: " << buffer << "\n";

    std::string message = "Hi Client";
    send(clientSocket, message.c_str(), message.size(), 0);
}