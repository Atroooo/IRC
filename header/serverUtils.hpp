#pragma once

#include "includes.hpp"

struct ServerArgument {
public:
    int port;
	char *password;
};

//Parsing
ServerArgument parsingArgument(int argc, char *argv[]);

//Server
int     setUpSocket(int port);

void    serverLoop(Server * server, char *serverPassword);

char    *getSubStrBuffer(char *buf, char *name);
bool    checkIfIn(char *buf, char *substr);
int     checkClient(Server *server, char *serverPassword);
bool    checkPassword(char *buf, char *serverPassword);
int     clientAction(int clientSocket, char *serverPassword, Server *server);

void    sendInfoClient(Server * server, int fd);
void    sendInfoChannel(Channel * channel, string msg, Server * server);
void    sendFunction(int fd, string msg);
void    sendInfoChannelOtherUsers(Channel * channel, string msg, Server *server, Client *sender);
void    sendInfoChannelOperator(Channel * channel, string msg, Server *server, Client *sender);