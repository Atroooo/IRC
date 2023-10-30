#include "../header/includes.hpp"
#include "../header/typedef.hpp"

vector<struct pollfd> setUpFds(int port){
    vector<struct pollfd> fds;
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
    vector<struct pollfd> fds = setUpFds(serverArgument.port);

    Server server(fds);

    serverLoop(&server, serverArgument.password);
    return 0;
}
