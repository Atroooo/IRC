#pragma once

#include "includes.hpp"
#include "typedef.hpp"
#include "Channel.hpp"

class Channel;

class Client {

    private:
        std::string                 _name;
        int                         _fd;
        std::map<string, Channel>   _channelsConnected;
        std::map<string, int>       _privileges;

    public:
        Client();
        ~Client();

        void setName(std::string name);
        std::string getName(void);

        void setFd(int fd);
        int getFd(void);

        void setChannel(Channel channel);
        Channel getChannel(void);

        //Gerer tous les privileges quand on cree user
};