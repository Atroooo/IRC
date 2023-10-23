#include "Client.hpp"

Client::Client(string name, int fd) {
    this->_name = name;
    this->_fd = fd;
}

Client::~Client() { }

string Client::getName() const { 
    return this->_name; 
}

int Client::getFd() const { 
    return this->_fd; 
}

void Client::setName(string name) { 
    this->_name = name; 
}

void Client::setFd(int fd) { 
    this->_fd = fd; 
}

void Client::addChannel(Channel channel) {
    this->_channelsConnected.insert(pair<string, Channel>(channel.getName(), channel));
}

bool Client::isInChannel(Channel channel) {
    map<string, Channel>::iterator it = this->_channelsConnected.find(channel.getName());
    if (it != this->_channelsConnected.end())
        return true;
    return false;
}