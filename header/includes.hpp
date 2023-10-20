#pragma once

#include <iostream>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <poll.h>
#include <map>
#include <list>
#include <vector>

using namespace std;

struct ServerArgument {
public:
    int port;
	char *password;
};

//parsing
ServerArgument parsingArgument(int argc, char *argv[]);
//SERVER
int setUpSocket(int port);
void serverLoop(vector<struct pollfd> fds, char *serverPassword);
void checkServer(pollfd & newFd, vector<struct pollfd> & fds);
void checkClient(vector<struct pollfd> & fds, char *serverPassword);
bool checkPassword(char *buf, char *serverPassword);

#include "Exception.hpp"


