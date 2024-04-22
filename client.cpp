#include <cstring>          // Include c string functions
#include <iostream>         // Include input/output operations
#include <netinet/in.h>     // Include structures for the internet domain address
#include <sys/socket.h>     // Include socket functions
#include <unistd.h>         // Include standard symbolic constants and types

int main()
{
    // Create a socket for the client with an IPv4 and a TCP connection
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Declare a structure to hold the server address information
    sockaddr_in serverAddress;          
    serverAddress.sin_family = AF_INET;              // Set family address to IPv4
    serverAddress.sin_port = htons(8080);           // Set port number to 8080
    serverAddress.sin_addr.s_addr = INADDR_ANY;    // Set IP address to INADDR_ANY to connect to any available network interface

    // Connect to the server 
    connect(clientSocket, (struct sockaddr*)&serverAddress,
    sizeof(serverAddress));

    // Declare a message to send to the server
    const char* message = "Hello Server!";

    // Send the message to the server
    send(clientSocket, message, std::strlen(message), 0);

    // Declare a buffer to store received data
    char buffer[1024] = {0};

    //Receive data from the server and store it in the buffer
    recv(clientSocket, buffer, sizeof(buffer), 0);

    // Print the received message from the server
    std::cout << "Message from server : "  << buffer << "\n";

    // Close the client socket
    close(clientSocket);
}