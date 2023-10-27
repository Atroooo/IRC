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
        int opt = poll(fdsVector.data(), fdsVector.size(), -1);
        if (opt < 0) {
            herror("poll");
            _exit(-1);
        }
        server.setList(fdsVector);
        sendInfoToClient(&server, newFd, serverPassword);
    }
}

/*---------------------------------------- Send Info -------------------------------------------*/
void sendInfoToClient(Server *server, struct pollfd newFd, char *serverPassword) {
    vector<struct pollfd> fds(server->getFdsList().begin(), server->getFdsList().end());
    for (size_t socketID = 0; socketID < fds.size(); socketID++) {
        if (fds[socketID].revents & POLLOUT){
            cout << "sending ..." << endl; 
            if (server->getCommandsToSend()[fds[socketID].fd] != "") {
                sendFunction(fds[socketID].fd, server->getCommandsToSend()[fds[socketID].fd]);
                server->getCommandsToSend()[fds[socketID].fd].clear();
            }
        }
        if (fds[socketID].revents & POLLIN) {
            cerr << "RECEIVING" << endl;
            if (fds[socketID].fd == server->getFd(0)->fd) {
                int clientSocket = waitClientConnection(fds[socketID].fd);
                newFd.fd = clientSocket;
                newFd.events = POLLIN;
                server->addToFds(newFd);
            }
            else {
                cout << "client action" << endl;
                checkClient(server, serverPassword);
                fds[socketID].events |= POLLOUT;
            }
        }
    }
}

void checkRetSend(int ret) {
    if (ret < 0) {
        cerr << "Error in send(). Quitting" << endl;
        //NEED EXIT
    }
}

void sendFunction(int fd, string msg) {
    int ret = send(fd, msg.c_str(), strlen(msg.c_str()), 0);
    checkRetSend(ret);
}
