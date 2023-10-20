#pragma once

#include "includes.hpp"
#include "typedef.hpp"
#include "Channel.hpp"

class Channel;

class Client {

    private:
        int                         _fd;
        string                      _name;
        map<std::string, Channel>   _channelsConnected;

    public:
        Client(string name, int fd);
        ~Client(void);

        void setName(std::string name);
        string getName(void);

        void setFd(int fd);
        int getFd(void);

        void addChannel(Channel channel);
        bool isInChannel(Channel channel);
};