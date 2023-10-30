#include "../../header/Client.hpp"

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
