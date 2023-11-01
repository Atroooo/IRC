#include "../../header/Commands.hpp"

//Gerer les cas ou l utilisateur n existe pas
Channel::Channel(string name, string password) {
    this->_name = name;
    this->_password = password;
    this->_topic = "No topic";
    if (!password.empty())
        this->_mode.push_back('k');
    this->_maxUsers = 10;
    _creationTime = get_time();
}

Channel::~Channel(void) { }

string Channel::getCreationTime(void) const {
    return this->_creationTime;
}

string Channel::getName(void) const {
    return this->_name;
}

string Channel::getPassword(void) const {
    return this->_password;
}

string Channel::getTopic(void) const {
    return this->_topic; 
}

list<char> Channel::getMode(void) const {
    return this->_mode; 
}

map<string, Client> Channel::getClients(void) const {
    return this->_clients;
}

int Channel::getMaxUsers(void) const {
    return this->_maxUsers; 
}

void Channel::setMaxUsers(int maxUsers) {
    if (maxUsers < 0)
        this->_maxUsers = 0;
    else if (maxUsers > 4095)
        this->_maxUsers = 10;
    else
        this->_maxUsers = maxUsers;
}

Client *Channel::getClient(string name) {
    map<string, Client>::iterator it = this->_clients.find(name);
    if (it != this->_clients.end())
        return &it->second;
    return NULL;
}

string Channel::getMembers(void) const {
    string members = "";
    for (map<string, Client>::const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        members += it->first;
        if (it != --this->_clients.end())
            members += " ";
    }
    return members;
}

string Channel::getChannelMembers(void) {
    string members = "";
    for (map<string, Client>::const_iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        if (this->isOperator(it->second))
            members += "@" + it->first;
        else
            members += it->first;
        if (it != --this->_clients.end())
            members += " ";
    }
    return members;
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

void Channel::addUser(Client client) {
    this->_clients.insert(pair<string, Client>(client.getName(), client));
}

void Channel::addOperator(Client client) {
    this->_operators.push_back(client);
}

void Channel::addInvited(Client client) {
    this->_isInvited.push_back(client);
}

void Channel::removeUser(Client client) {
    this->_clients.erase(client.getName());
}

void Channel::removeOperator(Client client) { 
    for (list<Client>::iterator i = this->_operators.begin(); i != this->_operators.end(); i++) {
        if ((*i).getName() == client.getName()) {
            this->_operators.erase(i);
            return ;
        }
    }
}

void Channel::unsetMode(char mode) {
    list<char>::iterator it = find(this->_mode.begin(), this->_mode.end(), mode);
    if (it != this->_mode.end())
        this->_mode.erase(it);
}

bool Channel::isUser(Client client) {
    map<string, Client>::iterator it = this->_clients.find(client.getName());
    if (it != this->_clients.end())
        return true;
    return false;
}

bool Channel::isOperator(Client client) {
    for (list<Client>::iterator i = this->_operators.begin(); i != this->_operators.end(); i++) {
        if ((*i).getName() == client.getName())
            return true;
    }
    return false;
}

bool Channel::isInvited(Client client) {
    for (list<Client>::iterator i = this->_isInvited.begin(); i != this->_isInvited.end(); i++) {
        if ((*i).getName() == client.getName())
            return true;
    }
    return false;
}

bool Channel::isModeSet(char mode) {
    list<char>::iterator it = find(this->_mode.begin(), this->_mode.end(), mode);
    if (it != this->_mode.end())
        return true;
    return false;
}