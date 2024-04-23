#include "server.h"

int main()
{
    UniquePointerOfServer& server = Server::GetInstance();
    
    int n = 2;

    try
    {
        server->start(n);
    }
    catch(SocketCreationFailedException& e)
    {
        std::cerr << e.message() << '\n';
    }
    catch(BindFailedException& e)
    {
        std::cerr << e.message() << '\n';
    }
    catch(ListenFailedException& e)
    {
        std::cerr << e.message() << '\n';
    }
    catch(MessageFailedException& e)
    {
        std::cerr << e.message() << '\n';
    }
    

    return 0;
}
