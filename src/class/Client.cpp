#include "../../header/Client.hpp"

Client::Client(string name, int fd) {
    this->_name = name;
    this->_username = "";
    this->_fd = fd;
    this->_passCheck = false;
    this->_isRegistered = false;
}

Client::Client(int fd) {
    this->_name = "";
    this->_username = "";
    this->_fd = fd;
    this->_passCheck = false;
    this->_isRegistered = false;
}

Client::~Client() { }

string Client::getName() const {
    return this->_name; 
}

int Client::getFd() const { 
    return this->_fd; 
}

list<string> Client::getCmdToSend(void) const { 
    return this->_cmdToSend; 
}

string Client::getUsername() const { 
    return this->_username; 
}

void Client::setName(string name) { 
    this->_name = name; 
}

void Client::setFd(int fd) { 
    this->_fd = fd; 
}

void Client::setUsername(string username) { 
    this->_username = username; 
}

bool Client::getPassCheck(void) const { 
    return this->_passCheck; 
}

void Client::addCmdToSend(string cmd) { 
    this->_cmdToSend.push_back(cmd); 
}

void Client::clearCmdToSend(void) { 
    this->_cmdToSend.clear(); 
}

void Client::setPassCheck(bool passCheck) { 
    this->_passCheck = passCheck; 
}