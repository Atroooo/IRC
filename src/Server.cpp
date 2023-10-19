#include "../header/includes.hpp"
#include "../header/Server.hpp"

Server::Server(int port, std::string password, vector<struct pollfd> fds) : _port(port), _password(password), _fds(fds){
}

Server::~Server() {
}

void setFd(std::string name, int fd) {
    _fds[name] = fd;
}
int  getFd(std::string name) {
    return _fds[name];
}

void setChannel(Channel channel) {
    _channels[channel.getId()] = channel;
}
map<int, Channel> getChannels(void){
    return _channels;
}

void setUser(Client client) {
    _clients.push_back(client);
}
vector<Client> getUser(void) {
    return _clients;
}

void setPassword(std::string password) {
    _password = password;
}
string getPassword(void) {
    return _password;
}

void setPort(int port){
    _port = port;
}
int getPort(void){
    return _port;
}