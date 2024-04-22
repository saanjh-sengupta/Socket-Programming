#include "client.h"

Client::~Client()
{
    if(clientSocket)
    {
        close(clientSocket);
    }
}

void Client::start()
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress));

    std::string message = "Hi Server";
    send(clientSocket, message.c_str(), message.size(), 0);

    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Message from server: " << buffer << "\n";
}