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
int setUpSocket(int port);
void serverLoop(list<struct pollfd> fds, char *serverPassword);
void checkServer(pollfd & newFd, Server & server);
void checkClient(Server *server, char *serverPassword);
bool checkPassword(char *buf, char *serverPassword);
char * getSubStrBuffer(char *buf, char *name);
void botAction(char *buf, int clientSocket, int x);
