#pragma once

#include "Channel.hpp"
#include "typedef.hpp"
#include "Client.hpp"
#include <sstream>

class Server {

    private:
        list<struct pollfd>&  _fds;
        size_t                  _serverFdsCount;
        list<Client>            _clients;
        list<Channel>           _channels;
    
    public:
        Server(list<struct pollfd> & fds);
        ~Server();

        void setList( vector<struct pollfd> fds);

        list<struct pollfd>& getFdsList() const { return this->_fds; };
        void addToFds(const struct pollfd& fd) {
            cout << "add to fds: " << fd.fd << endl;
            this->_fds.push_back(fd); };

        struct pollfd * getFd(size_t index);

        void setServChanCount(size_t count) { this->_serverFdsCount = count; };
        size_t getServChanCount() const { return this->_serverFdsCount; };

        void addClient(Client & client);
        list<Client> getClient(void) const;
        Client *getClient(string name);
        Client *getClient(int fd);

        void addChannel(Channel & channel);
        list<Channel> getChannel(void) const;
        Channel *getChannel(string name);
};
