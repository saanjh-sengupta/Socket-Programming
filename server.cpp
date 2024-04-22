#include "server.h"

SharedPointerOfServer Server::onlyObject = nullptr;

Server::~Server()
{
    for(int socket : clientSockets)
    {
        close(socket);
    }

    close(serverSocket);
}

SharedPointerOfServer Server::GetInstance()
{
    if(!onlyObject)
    {
        onlyObject.reset(new Server());
    }

    return onlyObject;
}

void Server::start()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress));

    listen(serverSocket, 5);

    int counter = 0;

    while(counter < 2)
    {
        int clientSock = accept(serverSocket, nullptr, nullptr);
        
        clientSockets.push_back(clientSock);
        char buffer[1024] = {0};

        recv(clientSock, buffer, sizeof(buffer), 0);

        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lk (mt);
        std::cout << "Message from client: " << buffer << "\n";

        std::string message = "Hi Client";
        send(clientSock, message.c_str(), message.size(), 0);

        counter++;
    }

   
}