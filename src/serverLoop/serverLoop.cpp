#include "../../header/includes.hpp"
#include "../../header/typedef.hpp"

void serverLoop(vector<struct pollfd> fds, char *serverPassword){
    struct pollfd newFd;
    while (true) {
        int opt = poll(fds.data(), (nfds_t) fds.size(), TIMEOUT);
        if (opt < 0) {
            herror("poll");
            _exit(-1);
        }
        checkServer(newFd, fds);
		checkClient(fds, serverPassword);
    }
}