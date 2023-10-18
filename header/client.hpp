#pragma once

#include "includes.hpp"
#include "typedef.hpp"
#include "channel.hpp"

class Client {

    private:
        std::string _name;
        int _fd;
        std::map<Channel, password> _channelsConnected;

    public:
        Client();
        ~Client();

        setName(std::string name);
        getName(std::string name);

        setFd(int fd);
        getFd(int fd);

        setChannel(Channel channel);
        getChannel(Channel channel);
}