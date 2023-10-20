#include "../../header/includes.hpp"
#include "../../header/typedef.hpp"
#include "../../header/Server.hpp"

void serverLoop(vector<struct pollfd> fds){
    struct pollfd newFd = {0, POLLIN, 0};
    Server server(fds);
    while (true) {
        int opt = poll(server.getFdsVec().data(), (nfds_t) fds.size(), TIMEOUT);
        if (opt < 0) {
            herror("poll");
            _exit(-1);
        }
        checkServer(newFd, server);
		checkClient(server);
    }
}