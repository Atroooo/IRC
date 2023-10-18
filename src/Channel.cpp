#include "../header/Commands.hpp"

// Channel::Channel(std::string name, std::string password) {
//     this->_name = name;
//     this->_password = password;
//     this->_topic = "No topic";
//     if (!password.empty())
//         this->_mode.push_back('k');
//     this->_maxUsers = 10;
// }

// // Channel(std::string name, std::string password, std::string topic) {
// //     this->_name = name;
// //     this->_password = password;
// //     this->_topic = topic;
// //     this->_mode = 't';
// // }

// // Channel(std::string name, std::string password, char mode) {
// //     this->_name = name;
// //     this->_password = password;
// //     this->_topic = "No topic";
// //     this->_mode = mode;
// // }

// // Channel(std::string name, std::string password, std::string topic, char mode) {
// //     this->_name = name;
// //     this->_password = password;
// //     this->_topic = topic;
// //     this->_mode = mode;
// // }

// Channel::~Channel() { }

// std::string Channel::getName() { 
//     return this->_name; 
// }

// std::string Channel::getPassword() { 
//     return this->_password; 
// }

// std::string Channel::getTopic() { 
//     return this->_topic; 
// }

// std::list<char> Channel::getMode() { 
//     return this->_mode; 
// }

// std::vector<Client> Channel::getUsers() { 
//     return this->_users; 
// }

// std::vector<Client> Channel::getOperators() { 
//     return this->_operators; 
// }

// int Channel::getMaxUsers() { 
//     return this->_maxUsers; 
// }

// int Channel::getFd() { 
//     return this->fd; 
// }

// void Channel::setTopic(std::string topic) { 
//     this->_topic = topic; 
// }

// void Channel::setMode(char mode) { 
//     this->_mode.push_back(mode); 
// }

// void Channel::setPassword(std::string password) { 
//     this->_password = password; 
// }

// void Channel::addUser(Client client) { 
//     this->_users.push_back(client); 
// }

// void Channel::addOperator(Client client) { 
//     this->_operators.push_back(client); 
// }

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
