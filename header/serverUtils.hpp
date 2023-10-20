#pragma once

#include "includes.hpp"

struct ServerArgument {
public:
    int port;
	char *password;
};

//parsing
ServerArgument parsingArgument(int argc, char *argv[]);
//SERVER
int setUpSocket(int port);
void serverLoop(list<struct pollfd> fds, char *serverPassword);
void checkServer(pollfd newFd, Server server);
void checkClient(Server server, char *serverPassword);
bool checkPassword(char *buf, char *serverPassword);

