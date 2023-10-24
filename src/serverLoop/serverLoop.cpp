#include "../../header/includes.hpp"
#include "../../header/typedef.hpp"
#include "../../header/Server.hpp"
#include <iostream>
#include <csignal>

bool	stopSignal = false;

static void	shutdown(int)
{
	stopSignal = true;
}

void serverLoop(list<struct pollfd> fds, char *serverPassword){
    struct pollfd newFd = {0, POLLIN, 0};
    Server server(fds);
    signal(SIGINT, shutdown);
    while (stopSignal == false) {
        vector<struct pollfd> fdsVector(server.getFdsList().begin(), server.getFdsList().end());
        int opt = poll(fdsVector.data(), (nfds_t) fdsVector.size(), TIMEOUT);
        if (opt < 0) {
            herror("poll");
            _exit(-1);
        }
        server.setList(fdsVector);
        checkServer(newFd, server);
		checkClient(&server, serverPassword);
    }
}