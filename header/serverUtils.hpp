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
void    checkClient(Server *server, char *serverPassword);
bool    checkPassword(char *buf, char *serverPassword);
int     clientAction(int clientSocket, char *serverPassword, Server *server);
char    *getSubStrBuffer(char *buf, char *name);
void    botAction(char *buf, int clientSocket, int x);