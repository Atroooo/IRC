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
        list<Client>            _operators;
        list<Client>            _isInvited;
        int                     _maxUsers;

    public:

        Channel(string name, string password);
        ~Channel(void);

        string                  getName(void) const;
        string                  getPassword(void) const;
        string                  getTopic(void) const;
        list<char>              getMode(void) const;
        map<string, Client>     getClients(void) const;
        int                     getMaxUsers(void) const;
        Client                  *getClient(string name);
        string                  getMembers(void) const;
        string                  getChannelMembers(void); 

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
