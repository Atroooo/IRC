#include "../header/includes.hpp"
#include "../header/typedef.hpp"

vector<struct pollfd> setUpFds(int port){
    vector<struct pollfd> fds;
    int listening = setUpSocket(port);
    struct pollfd listenerFd;
    listenerFd.fd = listening;
    listenerFd.events = POLLIN;
    listenerFd.revents = 1;
    fds.push_back(listenerFd);
    return fds;
}

int main(int argc, char *argv[])
{
    ServerArgument serverArgument = parsingArgument(argc, argv);
    vector<struct pollfd> fds = setUpFds(serverArgument.port);
    serverLoop(fds);

    return 0;
}
