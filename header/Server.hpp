#pragma once

#include "Channel.hpp"
#include "typedef.hpp"

class Server {

    private:
        std::map<std::string, int> _fds;
        std::map<Channel, int> _channels;
        std::vector<Client> _clients;
        std::string _password;
        int         _port;
    
    public:
        Server();
        ~Server();

        setFd(std::string name, int fd);
        getFd(std::string name);

        setChannel(Channel channel);
        getChannel(Channel channel);

        setUser(Client client);
        getUser(Client client);

        setPassword(std::string password);
        getPassword(std::string password);

        setPort(int port);
        getPort(int port);
};