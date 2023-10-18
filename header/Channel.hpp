#pragma once

#include "includes.hpp"
#include "Client.hpp"

class Channel {
    
    private:

        std::string             _name;
        std::string             _password;
        std::string             _topic;
        std::list<char>         _mode;
        std::vector<Client>     _users;
        std::vector<Client>     _operators;
        int                     _maxUsers;
        int                     fd;

    public:

        Channel(std::string name, std::string password);
        // Channel(std::string name, std::string password, std::string topic);
        // Channel(std::string name, std::string password, char mode);
        // Channel(std::string name, std::string password, std::string topic, char mode);
        ~Channel();

        std::string             getName();
        std::string             getPassword();
        std::string             getTopic();
        std::list<char>         getMode();
        std::vector<Client>     getUsers();
        std::vector<Client>     getOperators();
        int                     getMaxUsers();
        int                     getFd();

        void                    setTopic(std::string topic);
        void                    setMode(char mode);
        void                    setPassword(std::string password);
        void                    addUser(Client client);
        void                    addOperator(Client client);
        void                    removeUser(Client client);
        void                    removeOperator(Client client);
        void                    setMaxUsers(int maxUsers);

        bool                    isUser(Client client);
        bool                    isOperator(Client client);

};