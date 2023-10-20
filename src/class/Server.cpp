#include "../header/includes.hpp"
#include "../header/Server.hpp"
#include "../header/typedef.hpp"

Server::Server(list<struct pollfd> & fds) : _fds(fds) {
    _serverFdsCount = 1;
}

Server::~Server() {
    // for (size_t i = 0; i < _serverFdsCount; i++) {
    //     close(this->_fds[i].fd);
    // }
    // for (size_t i = 0; i < _clients.size(); i++) {
    //     this->_clients[i].~Client();
    // }
    // for (size_t i = 0; i < _channels.size(); i++) {
    //     this->_channels[i].~Channel();
    // }
}

struct pollfd & Server::getFd(size_t index) {
    for (list<struct pollfd>::iterator i = this->_fds.begin(); i != this->_fds.end(); i++) {
        if (i->fd == (int)index) {
            return *i;
        }
    }
    return *this->_fds.end(); //a fix
}

void Server::addClient(Client & client) {
    this->_clients.push_back(client);
}

list<Client> Server::getClient(void) {
    return this->_clients;
}

void    Server::addChannel(Channel & channel) {
    this->_channels.push_back(channel);
}

list<Channel> Server::getChannel(void) {
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