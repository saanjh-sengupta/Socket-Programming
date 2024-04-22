#include "client.h"

Client::Client(const std::string &message) : message{message}
{
}

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
    // inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress));

    send(clientSocket, message.c_str(), message.size(), 0);

    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::lock_guard<std::mutex> lk (mt);
    std::cout << "Message from server: " << buffer << "\n";

}