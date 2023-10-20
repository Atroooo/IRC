#include "../../header/includes.hpp"
#include "../../header/typedef.hpp"
#include "../../header/Server.hpp"

void serverLoop(list<struct pollfd> fds, char *serverPassword){
    struct pollfd newFd = {0, POLLIN, 0};
    Server server(fds);
    while (true) {
        vector<struct pollfd> fds(server.getFdsList().begin(), server.getFdsList().end());
        int opt = poll(fds.data(), (nfds_t) fds.size(), TIMEOUT);
        if (opt < 0) {
            herror("poll");
            _exit(-1);
        }
        checkServer(newFd, server);
		checkClient(server, serverPassword);
    }
}