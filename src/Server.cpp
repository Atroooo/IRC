#include "../header/includes.hpp"
#include "../header/Server.hpp"
#include "../header/typedef.hpp"

Server::Server(vector<struct pollfd> & fds) : _fds(fds) {
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

// void Server::addClient(Client client) {
//     this->_clients.push_back(client);
// }

// vector<Client> Server::getClient(std::string name) {
//     vector<Client>::iterator it = _clients.begin();
//     for (; it != _clients.end(); it++) {
//         if (it->getName() == name) {
//             return it;
//         }
//     }
//     return NULL;
// }

// void    Server::addChannel(Channel channel) {
//     this->_channels.push_back(channel);
// }

// vector<Channel> Server::getChannel(std::string name) {
//     vector<Channel>::iterator it = _channels.begin();
//     for (; it != _channels.end(); it++) {
//         if (it->getName() == name) {
//             return it;
//         }
//     }
//     return NULL;
// }