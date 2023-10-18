#include "../header/Commands.hpp"

Channel(std::string name, std::string password) {
    this->_name = name;
    this->_password = password;
    this->_topic = "No topic";
    if (!password.empty())
        this->_mode.push_back('k');
    this->_maxUsers = 10;
}

// Channel(std::string name, std::string password, std::string topic) {
//     this->_name = name;
//     this->_password = password;
//     this->_topic = topic;
//     this->_mode = 't';
// }

// Channel(std::string name, std::string password, char mode) {
//     this->_name = name;
//     this->_password = password;
//     this->_topic = "No topic";
//     this->_mode = mode;
// }

// Channel(std::string name, std::string password, std::string topic, char mode) {
//     this->_name = name;
//     this->_password = password;
//     this->_topic = topic;
//     this->_mode = mode;
// }

~Channel() { }

std::string Channel::getName() { 
    return this->_name; 
}

std::string Channel::getPassword() { 
    return this->_password; 
}

std::string Channel::getTopic() { 
    return this->_topic; 
}

char Channel::getMode() { 
    return this->_mode; 
}

std::vector</*Client*/> Channel::getUsers() { 
    return this->_users; 
}

std::vector</*Client*/> Channel::getOperators() { 
    return this->_operators; 
}

int Channel::getMaxUsers() { 
    return this->_maxUsers; 
}

int Channel::getFd() { 
    return this->fd; 
}

void Channel::setTopic(std::string topic) { 
    this->_topic = topic; 
}

void Channel::setMode(char mode) { 
    this->_mode.push_back(mode); 
}

void Channel::setPassword(std::string password) { 
    this->_password = password; 
}

void Channel::addUser(/*Client*/) { 
    this->_users.push_back(/*Client*/); 
}

void Channel::addOperator(/*Client*/) { 
    this->_operators.push_back(/*Client*/); 
}

void Channel::removeUser(/*Client*/) { 
    this->_users.erase(/*Client*/); 
}

void Channel::removeOperator(/*Client*/) { 
    this->_operators.erase(/*Client*/); 
}

bool Channel::isUser(/*Client*/) { 
    return (std::find(this->_users.begin(), this->_users.end(), /*Client*/) != this->_users.end()); 
}

bool Channel::isOperator(/*Client*/) { 
    return (std::find(this->_operators.begin(), this->_operators.end(), /*Client*/) != this->_operators.end()); 
}