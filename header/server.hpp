#pragma once

#include "includes.hpp"
#include "typedef.hpp"
#include "client.hpp"
#include "channel.hpp"

class Server {

    private:
        std::map<std::string, int fd> _fds;
        // objects
        std::map<Channel, int password> _channels;
        std::vector<Client> _clients;
    
    public:
        Server();
        ~Server();

        setFd(std::string name, int fd);
        getFd(std::string name);

        setChannel(Channel channel);
        getChannel(Channel channel);

        setUser(Client client);
        getUser(Client client);

};