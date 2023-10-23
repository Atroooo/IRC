#include "../header/includes.hpp"
#include "../header/Server.hpp"
#include "../header/typedef.hpp"

Server::Server(list<struct pollfd> & fds) : _fds(fds) {
    _serverFdsCount = 1;
}

Server::~Server() {
   
}

void Server::setList( vector<struct pollfd> fds) {
    copy(fds.begin(), fds.end(), this->_fds.begin());
}

struct pollfd * Server::getFd(size_t index) {
    size_t i = 0;

    for (list<struct pollfd>::iterator it = this->_fds.begin(); it != this->_fds.end(); it++) {
        if (i == index) {
            return &(*it);
        }
        i++;
    }
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

Channel *Server::getChannel(string name) {
    for (list<Channel>::iterator i = this->_channels.begin(); i != this->_channels.end(); i++) {
        if (i->getName() == name) {
            return &(*i);
        }
    }
    return NULL;
}