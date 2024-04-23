#include "client.h"

Client::Client(const std::string &message) : message{message} {}

// Client destructors deals with closing the client socket
Client::~Client()
{
    if(clientSocket)
    {
        close(clientSocket);
    }
}

void Client::start()
{
    // Creation of the client socket via IPv4 address with TCP connection and single protocol
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Corner case to check whether the client socket was successfully created or not
    if(clientSocket == -1)
    {
        throw SocketCreationFailedException("Error: Failed to create client socket\n", std::future_errc::no_state);
    }

    // Structure to hold the server address information
    serverAddress.sin_family = AF_INET;                             // Set address family to IPv4
    serverAddress.sin_port = htons(8080);                           // Set port number to 8080 (conversion of network into byte)
    serverAddress.sin_addr.s_addr = INADDR_ANY;                     // Set IP address to INADDR_ANY To listen to all available network interfaces
    // inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    // Establishing a connection with the server
    int connectValue = connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress));

    // Corner case to check whether the connection between the client and the server was successful or not
    if(connectValue == -1)
    {
        throw ClientConnectionFailedException("Error: Failed to connect the client with the server\n", std::future_errc::broken_promise);
    }

    // Sending message from the client to the server
    int bytesSent = send(clientSocket, message.c_str(), message.size(), 0);

    // Corner case to check whether the message was sent or not
    if(bytesSent == -1)
    {
        throw MessageFailedException("Error: Failed to send message to server\n", std::future_errc::no_state);
    }

    // Creating a buffer to store received data from the server
    char buffer[1024] = {0};

    // Receiving data from the server and storing it in the buffer
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

    // Corner case for checking whether the buffer has accepted data or not
    if(bytesReceived = 0 || bytesReceived == -1)
    {
        throw MessageFailedException("Error: Failed to receive message from client\n", std::future_errc::broken_promise);
    }

    // Displaying message from received from the server
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::lock_guard<std::mutex> lk (mt);
    std::cout << "Message from server: " << buffer << "\n";

}