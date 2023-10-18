#pragma once

#include "Channel.hpp"
#include "typedef.hpp"

class Server {

    private:
        std::map<std::string, int>  _fds;
        std::map<int, Channel>      _channels;
        std::vector<Client>         _clients;
        std::string                 _password;
        int                         _port;
    
    public:
        Server();
        ~Server();

        void setFd(std::string name, int fd);
        int  getFd(std::string name);

        void setChannel(Channel channel);
        map<int, Channel> getChannels(void);

        void setUser(Client client);
        vector<Client> getUser(void);

        void setPassword(std::string password);
        string getPassword(void);

        void setPort(int port);
        int getPort(void);
};