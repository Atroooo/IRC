#pragma once

#include "includes.hpp"
#include "typedef.hpp"
#include "Channel.hpp"

class Channel;

class Client {

    private:
        int                         _fd;
        string                      _name;
        bool                        _passCheck;
        list<string>                _cmdToSend;

    public:
        Client(string name, int fd);
        Client(int fd);
        ~Client(void);

        string getName(void) const;
        int getFd(void) const;
        bool getPassCheck(void) const { return this->_passCheck; };
        list<string> getCmdToSend(void) const { return this->_cmdToSend; };

        void setName(std::string name);
        void setFd(int fd);
        void addCmdToSend(string cmd) { this->_cmdToSend.push_back(cmd); };
        void clearCmdToSend(void) { this->_cmdToSend.clear(); };
        void setPassCheck(bool passCheck) { this->_passCheck = passCheck; };
};