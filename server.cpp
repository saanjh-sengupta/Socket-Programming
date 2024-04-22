#include "server.h"

UniquePointerOfServer Server::onlyObject = nullptr;

// Destructor of the server deals with closing the socket
Server::~Server()
{
    for(int socket : clientSockets)
    {
        close(socket);
    }

    close(serverSocket);
}

// Only a single instance of the server class is allowed to be created
UniquePointerOfServer& Server::GetInstance()
{
    // If object of the server class is not created then create a new instance of the Server (with it's value being resetted)
    if(!onlyObject)
    {
        onlyObject.reset(new Server());
    }

    return onlyObject;
}

void Server::start(int noOfTotalClients)
{
    // Creation of a server socket with IPv4 with TCP connection and uses a single protocol
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Corner case to check whether the socket creation of the server is successful or not
    if(serverSocket == -1)
    {
        throw SocketCreationFailedException("Error: Failed to create server socket\n", std::future_errc::no_state);
    }

    // A structure is declared to hold the server address information
    serverAddress.sin_family = AF_INET;             // IPv4 connection is being set
    serverAddress.sin_port = htons(8080);           // Port 8080 is being accessed
    serverAddress.sin_addr.s_addr = INADDR_ANY;     // IP Address is set to INADDR_ANY to listen to all available network interfaces

    // Bind the socket into the server
    int bindValue = bind(serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress));
    // int bindValue = bind(serverSocket, static_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress));


    // Corner case to check whether the bind was successful or not
    if(bindValue == -1)
    {
        throw BindFailedException("Error: Failed to bind the server socket", std::future_errc::no_state);
    }
    
    // Make the server listen to the incoming connections with a transmission queue size of 5
    int listenValue = listen(serverSocket, 5);

    // Corner case to check whether the listening queue size has valid data or not
    if(listenValue == -1)
    {
        throw ListenFailedException("Error: Failed to listen on the server socket\n", std::future_errc::broken_promise);
    }

    int counter = 0;

    // Counter is set to run a loop till all the clients have interacted with the server
    while(counter < noOfTotalClients)
    {
        // Accepting incoming client connection
        int clientSock = accept(serverSocket, nullptr, nullptr);

        // Corner case to check the validity of the client connection
        if(clientSock == -1)
        {
            throw ClientConnectionFailedException("Error: Failed to listen on server socket\n", std::future_errc::no_state);
        }
        
        clientSockets.emplace_back(clientSock);
        
        // Declare a buffer to store the data received by the client
        char buffer[1024] = {0};

        // Receiving data from the client and storing it in the buffer
        int bytesReceived = recv(clientSock, buffer, sizeof(buffer), 0);

        // Checking the validity of the received data in the buffer
        if(bytesReceived == -1 || bytesReceived == 0)
        {
            throw MessageFailedException("Error: Failed to receive message from client\n", std::future_errc::broken_promise);
        }

        // Critical section (cout stream)
        std::lock_guard<std::mutex> lk (mt);

        // Displaying message received from the client
        std::cout << "Message from client: " << buffer << "\n";


        std::string message;
        std::cout << "Enter message to be sent back to the client: ";
        std::getline(std::cin, message);
        
        // Sending a reply back to the client
        send(clientSock, message.c_str(), message.size(), 0);

        counter++;
    }   
}