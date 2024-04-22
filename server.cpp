#include <iostream>             // Includes input output streams
#include <string>               // Includes string functional use cases
#include <netinet/in.h>         // Includes structures for accessing internet domain address
#include <sys/socket.h>         // Includes socket functions
#include <unistd.h>             // Include standard symbolic constants

int main()
{
    // Created a server socket of IPv4 and TCP connection
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Declare a structure to hold server address information
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;             // IPv4 connection is being set
    serverAddress.sin_port = htons(8080);           // Port 8080 being accessed
    serverAddress.sin_addr.s_addr = INADDR_ANY;     // Set to INADDR_ANY to connect to any available network interface

    // Bind the socket into the server. 
    // Reinterpret_cast is used to convert sockaddr* into struct sockaddr*
    bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress));
    listen(serverSocket, 5);    // Made the server listen to incoming connections with a queue size of 5

    // Accept incoming client connection
    int clientSocket = accept(serverSocket, nullptr, nullptr);

    // Buffer created to store receieved data
    char buffer[1024] = {0};

    // Client incoming data is being stored into the buffer
    recv(clientSocket, buffer, sizeof(buffer), 0);

    // Client message is being printed
    std::cout << "Message from client: " << buffer << "\n";

    // String message being formulated from server
    std::string message = "Hi Client";

    // Sever message is being sent to the client
    send(clientSocket, message.c_str(), message.size(), 0);

    // Server socket is being closed
    close(serverSocket);

    return 0;

}