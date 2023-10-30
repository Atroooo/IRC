#include "../../header/includes.hpp"
#include "../../header/typedef.hpp"
#include "../../header/Server.hpp"

bool	stopSignal = false;

static void	shutdown(int) { stopSignal = true; }

void serverLoop(Server * server, char *serverPassword) {
    int             pollReturn;
    vector<struct pollfd> fds = server->getFdsVector();
    struct pollfd   newFd;

    signal(SIGINT, shutdown); 
    while (stopSignal == false) {
        // vector<struct pollfd> fds = server->getFdsVector();

        pollReturn = poll(fds.data(), fds.size(), -1);
        if (pollReturn < 0) {
            herror("poll");
            _exit(-1);
        } 
        if (pollReturn == 0) {
			std::cerr << "Error: poll() timed out" << std::endl;
			break ;
		}
        // server->setVector(fds);
        for (size_t socketID = 0; socketID < fds.size(); socketID++) {
            std::cout << "===> " << fds[socketID].revents << std::endl;
            if (fds[socketID].revents & POLLOUT){
                cout << "SENDING" << endl; 
                // _exit(0);
            }
            if (fds[socketID].revents & POLLIN) {
                cerr << "RECEIVING" << endl;
                if (fds[socketID].fd == server->getFd(0)->fd) {
                    int clientSocket = waitClientConnection(fds[socketID].fd);
                    // Set the socket to be non-blocking (the sockets created after will inherit)
                    int flags = fcntl(clientSocket, F_GETFL, 0);
                    flags |= O_NONBLOCK;
                    fcntl(clientSocket, F_SETFL, flags);
                    newFd.fd = clientSocket;
                    newFd.events = POLLIN;
                    fds.push_back(newFd);
                    // server->addToFds(newFd);
                }
                else {
                    cout << "client action" << endl;
                    // checkClient(server, serverPassword);
                    // clientAction(fds[socketID].fd, serverPassword, server);
                    fds[socketID].events |= POLLOUT;
                }
            }
        }
    }
}

/*---------------------------------------- Send Info -------------------------------------------*/
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
