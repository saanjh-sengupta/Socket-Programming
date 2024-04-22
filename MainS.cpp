#include "server.h"

int main()
{
    SharedPointerOfServer server = Server::GetInstance();
    
    std::thread th1 = std::thread(&Server::start, server);

    th1.join();
    
    return 0;
}