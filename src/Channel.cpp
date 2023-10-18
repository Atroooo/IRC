#include "../header/Commands.hpp"

Channel::Channel(string name, string password) {
    this->_name = name;
    this->_password = password;
    this->_topic = "No topic";
    if (!password.empty())
        this->_mode.push_back('k');
    this->_maxUsers = 10;
}

// Channel(string name, string password, string topic) {
//     this->_name = name;
//     this->_password = password;
//     this->_topic = topic;
//     this->_mode = 't';
// }

// Channel(string name, string password, char mode) {
//     this->_name = name;
//     this->_password = password;
//     this->_topic = "No topic";
//     this->_mode = mode;
// }

// Channel(string name, string password, string topic, char mode) {
//     this->_name = name;
//     this->_password = password;
//     this->_topic = topic;
//     this->_mode = mode;
// }

Channel::~Channel() { }

string Channel::getName() { 
    return this->_name; 
}

string Channel::getPassword() { 
    return this->_password; 
}

string Channel::getTopic() { 
    return this->_topic; 
}

list<char> Channel::getMode() { 
    return this->_mode; 
}

map<string, Client> Channel::getUsers() { 
    return this->_clients; 
}

int Channel::getMaxUsers() { 
    return this->_maxUsers; 
}

int Channel::getFd() { 
    return this->fd; 
}

void Channel::setTopic(string topic) { 
    this->_topic = topic; 
}

void Channel::setMode(char mode) { 
    this->_mode.push_back(mode); 
}

void Channel::setPassword(string password) { 
    this->_password = password; 
}

void Channel::addUser(Client client, int privilege) {
    this->_clients[client.getName()] = client;
    //add privilege to client
    (void)privilege;
}

// void Channel::removeUser(Client client) {
//     vector<Client>::iterator i = find(this->_users.begin(), this->_users.end(), client);
//     this->_users.erase(i);
// }

// void Channel::removeOperator(Client client) { 
//     vector<Client>::iterator i = find(this->_operators.begin(), this->_operators.end(), client);
//     this->_operators.erase(i);
// }

// bool Channel::isUser(Client client) {
//     vector<Client>::iterator it = find(this->_users.begin(), this->_users.end(), client);
//     // if (it != this->_users.end())
//     //     return true;
//     return false;
// }

// bool Channel::isOperator(Client client) {
//     vector<Client>::iterator it = find(this->_operators.begin(), this->_operators.end(), client);
//     // if (it != this->_operators.end())
//     //     return true;
//     return false;
// }
