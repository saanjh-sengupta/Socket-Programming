#include <cstring>              // Includes C string functions
#include <iostream>             // Includes input/output stream functions
#include <netinet/in.h>         // Include structures for internet domain addresses
#include <sys/socket.h>         // Include socket functions
#include <unistd.h>             // Include standard symbolic constant and types

int main()
{
    // Create a socket for the server with IPv4 and TCP connection
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Declaring a structure to hold the server address information
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;             // Set address family to IPv4
    serverAddress.sin_port = htons(8080);           // Set port number to 8080 (converted to netwrok byte order)
    serverAddress.sin_addr.s_addr = INADDR_ANY;     // Set IP address to INADDR_ANY to listen to all available network interfaces

    // Bind the socket into the server
    bind(serverSocket, (struct sockaddr*)&serverAddress,
                    sizeof(serverAddress));

    // Make the server listen to the incoming connections with a queue size of 5
    listen(serverSocket, 5);

    // Accepting an incoming client connection
    int clientSocket = accept(serverSocket, nullptr, nullptr);

    // Declare a buffer to store received data
    char buffer[1024] = {0};

    // Receive data from the client and store it in the buffer
    recv(clientSocket, buffer, sizeof(buffer), 0);

    // Print the received message from the client
    std::cout << "Message from client: " << buffer << "\n";

    // Declare a message to send back to the client
    const char* message = "Hi Client";

    // Send the message back to the client
    send(clientSocket, message, std::strlen(message), 0);

    close(clientSocket);     // Close the client socket
    close(serverSocket);    // Close the server socket
}