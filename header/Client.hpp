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

        string getName(void) const;
        int getFd(void) const;

        void setName(std::string name);
        void setFd(int fd);
        void addChannel(Channel channel);

        bool isInChannel(Channel channel);
};