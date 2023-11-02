#pragma once

#include "includes.hpp"
#include "typedef.hpp"
#include "Channel.hpp"

class Channel;

class Client {

    private:
        int                         _fd;
        string                      _name;
        string                      _username;
        bool                        _passCheck;
        list<string>                _cmdToSend;

    public:
        Client(string name, int fd);
        Client(int fd);
        ~Client(void);

        string getName(void) const;
        int getFd(void) const;
        bool getPassCheck(void) const;
        list<string> getCmdToSend(void) const;
        string getUsername(void) const;

        void setName(std::string name);
        void setFd(int fd);
        void setUsername(std::string username);
        void addCmdToSend(string cmd);
        void clearCmdToSend(void);
        void setPassCheck(bool passCheck);
};