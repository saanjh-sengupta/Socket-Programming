#include "client.h"

int main()
{
    Client client1("I am Client 1");
    Client client2("I am client 2");
    
    std::thread th2 = std::thread(&Client::start, &client1);
    std::thread th3 = std::thread(&Client::start, &client2);

    th2.join();
    th3.join();
    return 0;
}