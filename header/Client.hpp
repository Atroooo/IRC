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
        string                      _buffer;

    public:
        Client(string name, int fd);
        Client(int fd);
        ~Client(void);

        string getName(void) const;
        int getFd(void) const;
        bool getPassCheck(void) const;
        list<string> getCmdToSend(void) const;
        string getUsername(void) const;
        string& getBuffer() { return this->_buffer; };
        void addToBuffer(string buffer) { this->_buffer += buffer; };

        void setName(std::string name);
        void setFd(int fd);
        void setBuffer(string buffer) { this->_buffer = buffer; };
        void setUsername(std::string username);
        void addCmdToSend(string cmd);
        void clearCmdToSend(void);
        void setPassCheck(bool passCheck);
};