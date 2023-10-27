#include "../../header/includes.hpp"
#include "../../header/typedef.hpp"
#include <sys/poll.h>
#include <unistd.h>

int acceptNewConnection(int listening){
    int clientSocket = accept(listening, NULL, NULL);
    cout  << "new socket created " << endl;
	return clientSocket;
}

void checkServer(pollfd & newFd, Server & server){
    if (server.getFd(0)->revents != POLLIN )
        return;
    int clientSocket = acceptNewConnection(server.getFd(0)->fd);
    cout << "listen = " << server.getFd(0)->fd << endl;
    newFd.fd = clientSocket;
    newFd.events = POLLIN;
    server.addToFds(newFd);
}