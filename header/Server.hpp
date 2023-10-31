#pragma once

#include "Channel.hpp"
#include "typedef.hpp"
#include "Client.hpp"
#include <sstream>

class Server {

    private:
        vector<struct pollfd>&  _fds;
        size_t                  _serverFdsCount;
        list<Client>            _clients;
        list<Channel>           _channels;
    
    public:
        Server(vector<struct pollfd>& fds);
        ~Server();

        vector<struct pollfd>& getFdsVector() const { return this->_fds; };

        struct pollfd * getFd(size_t index);
        size_t getServChanCount() const { return this->_serverFdsCount; };
        list<Client> getClient(void) const;
        Client *getClient(string name);
        Client *getClient(int fd);
        list<Channel> getChannel(void) const;
        Channel *getChannel(const string & name);

        void setVector(vector<struct pollfd> fds);
        void setServChanCount(size_t count) { this->_serverFdsCount = count; };
        void addToFds(const struct pollfd& fd) { this->_fds.push_back(fd); };
        void addClient(Client & client);
        void addChannel(Channel & channel);
        void printClients();
};

void sendInfoToClient(Server *server, struct pollfd newFd, char *serverPassword);
void sendFunction(int fd, string msg);
void checkRetSend(int ret);
int waitClientConnection(int listening);
