#include "../header/includes.hpp"
#include "../header/typedef.hpp"

list<struct pollfd> setUpFds(int port){
    list<struct pollfd> fds;
    struct pollfd listenerFd;

    int listening = setUpSocket(port);
    listenerFd.fd = listening;
    listenerFd.events = POLLIN;
    fds.push_back(listenerFd);
    
    return fds;
}

int main(int argc, char *argv[])
{
    ServerArgument serverArgument = parsingArgument(argc, argv);
    list<struct pollfd> fds = setUpFds(serverArgument.port);
    serverLoop(fds, serverArgument.password);
    return 0;
}
