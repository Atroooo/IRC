#pragma once

#include "includes.hpp"
#include "Client.hpp"

class Client;

class Channel {
    
    private:

        string                  _name;
        string                  _password;
        string                  _topic;
        list<char>              _mode;
        map<string, Client>     _clients;
        vector<Client>          _operators;
        vector<Client>          _isInvited;
        int                     _maxUsers;
        int                     fd;

    public:

        Channel(string name, string password);
        ~Channel(void);

        string                  getName(void);
        string                  getPassword(void);
        string                  getTopic(void);
        list<char>              getMode(void);
        map<string, Client>     getUsers(void);
        int                     getMaxUsers(void);
        int                     getFd(void);

        void                    setTopic(string topic);
        void                    setMode(char mode);
        void                    setPassword(string password);
        void                    addUser(Client client);
        void                    addOperator(Client client);
        void                    addInvited(Client client);
        void                    removeUser(Client client);
        void                    removeOperator(Client client);
        void                    setMaxUsers(int maxUsers);

        bool                    isUser(Client client);
        bool                    isOperator(Client client);
        bool                    isInvited(Client client);

};
