#pragma once

#include "includes.hpp"
#include "Client.hpp"

class Client;

class Channel {
    
    private:

        string             _name;
        string             _password;
        string             _topic;
        list<char>         _mode;
        map<string, Client>   _clients;
        int                _maxUsers;
        int                fd;

    public:

        Channel(string name, string password);
        // Channel(string name, string password, string topic);
        // Channel(string name, string password, char mode);
        // Channel(string name, string password, string topic, char mode);
        ~Channel();

        string                  getName();
        string                  getPassword();
        string                  getTopic();
        list<char>              getMode();
        map<string, Client>     getUsers();
        int                     getMaxUsers();
        int                     getFd();

        void                    setTopic(string topic);
        void                    setMode(char mode);
        void                    setPassword(string password);
        void                    addUser(Client client, int privilege);
        void                    removeUser(Client client);
        void                    removeOperator(Client client);
        void                    setMaxUsers(int maxUsers);

        bool                    isUser(Client client);
        bool                    isOperator(Client client);

};
