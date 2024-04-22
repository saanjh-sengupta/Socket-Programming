#include <iostream>                 // Includes input output streams
#include <string>                   // Includes string functions
#include <netinet/in.h>             // Includes structures for storing and accessing the internet domain access
#include <sys/socket.h>             // Includes socket functions
#include <unistd.h>                 // Includes standard symbolic constraints

int main()
{
    // Created a client socket with IPv4 and TCP connection 
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Declaring a structure to hold the server address information 
    sockaddr_in serverAddress;  
    serverAddress.sin_family = AF_INET;                     // Supports IPv4 connections
    serverAddress.sin_port = htons(8080);                   // Port 8080 is being used to establish the connection
    serverAddress.sin_addr.s_addr = INADDR_ANY;             // Set to INADDR_ANY to listen to all available incoming connection

    // Connection being established with the server
    // reinterpret_cast is being used to convert sockaddr* into struct sockaddr*
    connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress));

    // String message being allocated in the stack memory 
    std::string message = "Hello Server";

    // Client socket will be sending the message to the server socket
    send(clientSocket, message.c_str(), message.size(), 0);

    // Character buffer being allocated to accept messages from the server
    char buffer[1024] = {0};

    // Information being received from the server
    recv(clientSocket, buffer, sizeof(buffer), 0);

    // Printing the message being sent from the server
    std::cout << "Message from server: " << buffer << "\n";

    // Close the client socket
    close(clientSocket);

    return 0;
}