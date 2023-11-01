#pragma once

#include "includes.hpp"

struct ServerArgument {
public:
    int port;
	char *password;
};

/*--------------- Parsing functions ---------------*/
ServerArgument parsingArgument(int argc, char *argv[]);

/*--------------- Server functions ---------------*/
int     setUpSocket(int port);
void    serverLoop(Server * server, char *serverPassword);

/*--------------- Client functions ---------------*/
char    *getSubStrBuffer(char *buf, char *name);
bool    checkIfIn(char *buf, char *substr);
int     checkClient(Server *server, char *serverPassword);
bool    checkPassClient(Client *client, string bufStr, char *serverPassword, Server * server);
bool    checkNickClient(Client *client, string bufStr, Server *server);
bool    checkEndOfLine(string bufStr);
int     clientAction(int clientSocket, char *serverPassword, Server *server);

/*---------------- Send functions ----------------*/
void    sendInfoClient(Server * server, int fd);
void    sendInfoChannel(Channel * channel, string msg, Server * server);
void    sendFunction(int fd, string msg);
void    sendInfoChannelOtherUsers(Channel * channel, string msg, Server *server, Client *sender);
void    sendInfoChannelOperator(Channel * channel, string msg, Server *server, Client *sender);

void    removeEmptyChannel(Server *server);