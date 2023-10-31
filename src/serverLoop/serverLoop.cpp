#include "../../header/includes.hpp"
#include "../../header/typedef.hpp"
#include "../../header/Server.hpp"

bool	stopSignal = false;

static void	shutdown(int) { stopSignal = true; }

void serverLoop(Server * server, char *serverPassword) {
    vector<struct pollfd>   fds = server->getFdsVector();
    struct pollfd           newFd;
    int                     pollReturn;

    signal(SIGINT, shutdown);

    while (stopSignal == false) {
        
        pollReturn = poll(fds.data(), fds.size(), -1);
        if (pollReturn < 0) {
            herror("poll");
            _exit(-1);
        } 
        if (pollReturn == 0) {
			std::cerr << "Error: poll() timed out" << std::endl;
			break ;
		}

        for (size_t socketID = 0; socketID < fds.size(); socketID++) {

            if (fds[socketID].revents & POLLOUT){
                cout << "SENDING" << endl; 
                // _exit(0);
            }
            if (fds[socketID].revents & POLLIN) {

                if (fds[socketID].fd == server->getFd(0)->fd) {
                    //Create a new socket for the client
                    int clientSocket = accept(fds[socketID].fd, NULL, NULL);
                    newFd.fd = clientSocket;
                    newFd.events = POLLIN;
                    fds.push_back(newFd);
                }

                else {
                    checkClient(server, serverPassword);
                    clientAction(fds[socketID].fd, serverPassword, server);
                    fds[socketID].events |= POLLOUT;
                }
            }
        server->setVector(fds);
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
