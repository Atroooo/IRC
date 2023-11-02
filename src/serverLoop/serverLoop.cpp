#include "../../header/includes.hpp"
#include "../../header/typedef.hpp"
#include "../../header/Server.hpp"

bool	stopSignal = false;

static void	shutdown(int) { stopSignal = true; }

/*---------------------------------------- Create Client -------------------------------------------*/
void createClient(Server *server, int clientSocket) {
    Client client(clientSocket);
    server->addClient(client);
}

/*---------------------------------------- Server Loop -------------------------------------------*/
void serverLoop(Server * server, char *serverPassword) {
    vector<struct pollfd>   fds = server->getFdsVector();
    struct pollfd           newFd = {0, POLLIN, 0};
    int                     pollReturn;

    signal(SIGINT, shutdown);

    while (stopSignal == false) {
        pollReturn = poll(fds.data(), fds.size(), -1);
        if (pollReturn < 0) {
            herror("poll");
            _exit(-1);
        } 
        if (pollReturn == 0) {
			serverLog("Poll ", "Timeout", RED);
			break ;
		}
        for (size_t socketID = 0; socketID < fds.size(); socketID++) {
            
            if (fds[socketID].revents & POLLOUT) {
                sendInfoClient(server, fds[socketID].fd);
            }

            if (fds[socketID].revents & POLLIN) {
                if (fds[socketID].fd == server->getFd(0)->fd) {
                    int clientSocket = accept(fds[socketID].fd, NULL, NULL);
                    newFd.fd = clientSocket;
                    newFd.events = POLLIN;
                    fds.push_back(newFd);
                    server->setVector(fds);
                    createClient(server, clientSocket);
                    serverLog("Client ", "Connected", GREEN);
                }
                else {
                    if (checkClient(server, serverPassword) == 0) {
                        Client *cli = server->getClient(fds[socketID].fd);
                        if (cli == NULL)
                            continue;
                        serverLog("Client disconnected", "",RED);
                        leaveAllChannels(cli, server);
                        server->removeClient(cli->getFd());
                        fds.erase(fds.begin() + socketID);
                        server->setVector(fds);
                        continue;
                    }
                    fds[socketID].events |= POLLOUT;
                }
            }
        }
        removeEmptyChannel(server);
    }
    closeAllFds(server);
    serverLog("Server ", "Closed", RED);
}

/*---------------------------------------- Send Info -------------------------------------------*/
void sendInfoClient(Server * server, int fd) {
    Client *client = server->getClient(fd);
    if (client == NULL) {
        return ;
    }
    list<string> cmdToSend = client->getCmdToSend();
    if (cmdToSend.size() == 0) {  
        return ;
    }
    serverLog("Send ", "Info to " + client->getName(), GREEN);
    for (list<string>::iterator it = cmdToSend.begin(); it != cmdToSend.end(); it++) {
        serverLog("Send ", *it, GREEN);
        sendFunction(fd, *it);
    }
    client->clearCmdToSend();
}

void checkRetSend(int ret) {
    if (ret < 0) {
        serverLog("Send ", "Error", RED);
        _exit(-1);
    }
}

void sendFunction(int fd, string msg) {
    int ret = send(fd, msg.c_str(), strlen(msg.c_str()), 0);
    checkRetSend(ret);
}

void sendInfoChannel(Channel * channel, string msg, Server *server) {
    map<string, Client> members = channel->getClients();
    for (map<string, Client>::iterator it = members.begin(); it != members.end(); it++) {
        Client *client = server->getClient(it->second.getFd());
        if (client == NULL) {
            continue;
        }
        client->addCmdToSend(msg);
    }
}

void sendInfoChannelOtherUsers(Channel * channel, string msg, Server *server, Client *sender) {
    map<string, Client> members = channel->getClients();
    for (map<string, Client>::iterator it = members.begin(); it != members.end(); it++) {
        if (it->second.getName() == sender->getName()) {
            continue;
        }
        Client *client = server->getClient(it->second.getFd());
        if (client == NULL) {
            continue;
        }
        client->addCmdToSend(msg);
    }
}

void sendInfoChannelOperator(Channel * channel, string msg, Server *server, Client *sender) {
    map<string, Client> members = channel->getClients();
    for (map<string, Client>::iterator it = members.begin(); it != members.end(); it++) {
        if (channel->isOperator(it->second) && it->second.getName() != sender->getName()) {
            Client *client = server->getClient(it->second.getFd());
            if (client == NULL) {
                continue;
            }
            client->addCmdToSend(msg);
        }
    }
}

/*---------------------------------------- Remove Empty Channel -------------------------------------------*/
void checkIfClientIsStillConnected(Server * server, Channel *channel) {
    map<string, Client> members = channel->getClients();
    for (map<string, Client>::iterator it = members.begin(); it != members.end(); it++) {
        if (server->isClient(it->second.getFd()) == false) {
            channel->removeUser(it->second);
        }
    }
}

void removeEmptyChannel(Server *server) {
    list<Channel> channels = server->getChannel();
    for (list<Channel>::iterator it = channels.begin(); it != channels.end(); it++) {
        checkIfClientIsStillConnected(server, &(*it));
        if (it->getClients().size() == 0) {
            server->removeChannel(it->getName());
            serverLog("Channel", " deleted", RED);
        }
    }
}

/*---------------------------------------- Close All Fds -------------------------------------------*/
void closeAllFds(Server *server) {
    vector<struct pollfd> fds = server->getFdsVector();
    for (size_t i = 0; i < fds.size(); i++) {
        close(fds[i].fd);
    }
}

/*----------------------------------------- Logs ---------------------------------------------------*/
void serverLog(string cmd, string msg, string color) {
    cout << color << cmd << RESET << msg << endl;
}