#pragma once

#include "Channel.hpp"
#include "typedef.hpp"
#include "Client.hpp"

class Server {

    private:
        vector<struct pollfd>&  _fds;
        size_t                  _serverFdsCount;
        list<Client>            _clients;
        list<Channel>           _channels;
    
    public:
        Server(vector<struct pollfd> & fds);
        ~Server();

        vector<struct pollfd>& getFdsVec() { return this->_fds; };
        void addToFds(struct pollfd fd) { this->_fds.push_back(fd); };

        struct pollfd & getFd(size_t index) { return this->_fds[index]; };

        void setServChanCount(size_t count) { this->_serverFdsCount = count; };
        size_t getServChanCount() { return this->_serverFdsCount; };

        void addClient(Client client);
        list<Client> getClient(void);

        void addChannel(Channel channel);
        list<Channel> getChannel(void);
        Channel *getChannel(string name);
};
