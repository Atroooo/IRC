#include "../../header/includes.hpp"
#include "../../header/Server.hpp"
#include "../../header/typedef.hpp"

Server::Server(vector<struct pollfd> & fds) : _fds(fds) {
    _serverFdsCount = 1;
}

Server::~Server() { }

void Server::setVector(vector<struct pollfd> fds) {
    this->_fds = fds;
}

struct pollfd * Server::getFd(size_t index) {
    if (index < this->_fds.size())
        return &this->_fds[index];
    return NULL;
}

void Server::addClient(Client & client) {
    this->_clients.push_back(client);
}

list<Client> Server::getClient(void) const {
    return this->_clients;
}

Client *Server::getClient(string name) {
    for (list<Client>::iterator i = this->_clients.begin(); i != this->_clients.end(); i++) {
        if (i->getName() == name) {
            return &(*i);
        }
    }
    return NULL;
}

Client *Server::getClient(int fd) {
    for (list<Client>::iterator i = this->_clients.begin(); i != this->_clients.end(); i++) {
        if (i->getFd() == fd) {
            return &(*i);
        }
    }
    return NULL;
}

void    Server::addChannel(Channel & channel) {
    this->_channels.push_back(channel);
}

list<Channel> Server::getChannel(void) const {
    return this->_channels;
}

Channel *Server::getChannel(const string & name) {
    for (list<Channel>::iterator i = this->_channels.begin(); i != this->_channels.end(); i++) {
        if (i->getName().compare(name) == 0) {
            return &(*i);
        }
    }
    return NULL;
}

void Server::printClients(){
    for (list<Client>::iterator it = this->_clients.begin(); it != this->_clients.begin(); it ++) {
        cout << it->getName() << endl;
    }
}

void Server::removeClient(int fd) {
    for (list<Client>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        if (it->getFd() == fd) {
            this->_clients.erase(it);
            break;
        }
    }
}

void Server::removeChannel(string name) {
    for (list<Channel>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
        if (it->getName() == name) {
            this->_channels.erase(it);
            break;
        }
    }
}