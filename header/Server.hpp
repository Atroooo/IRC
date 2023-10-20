#pragma once

#include "Channel.hpp"
#include "typedef.hpp"
#include "Client.hpp"

class Server {

    private:
        std::vector<struct pollfd>&  _fds;
        size_t                       _serverFdsCount;
        std::vector<Client>         _clients;
        std::vector<Channel>        _channels;
    
    public:
        Server(vector<struct pollfd> & fds);
        ~Server();

        vector<struct pollfd>& getFdsVec() { return this->_fds; };
        void addToFds(struct pollfd fd) { this->_fds.push_back(fd); };

        struct pollfd & getFd(size_t index) { return this->_fds[index]; };

        void setServChanCount(size_t count) { this->_serverFdsCount = count; };
        size_t getServChanCount() { return this->_serverFdsCount; };

        // void addClient(Client client);
        // Client getClient(std::string name);

        // void addChannel(Channel channel);
        // Channel getChannel(std::string name);

};
