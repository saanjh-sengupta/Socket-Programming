#include "client.h"

int main()
{

    Client client1("Hey, I am Client 1");
    Client client2("Hi, I am Client 2");

    std::future<void> th1 = std::async(&Client::start, std::ref(client1));
    std::future<void> th2 = std::async(&Client::start, std::ref(client2));
 
    try
    {
        th1.wait();
    }
    catch(SocketCreationFailedException& e)
    {
        std::cerr << e.message() << '\n';
    }
    catch(MessageFailedException& e)
    {
        std::cerr << e.message() << '\n';
    }
    catch(ClientConnectionFailedException& e)
    {
        std::cerr << e.message() << '\n';
    }

    try
    {
        th2.wait();
    }
    catch(SocketCreationFailedException& e)
    {
        std::cerr << e.message() << '\n';
    }
    catch(MessageFailedException& e)
    {
        std::cerr << e.message() << '\n';
    }
    catch(ClientConnectionFailedException& e)
    {
        std::cerr << e.message() << '\n';
    }

    return 0;


}