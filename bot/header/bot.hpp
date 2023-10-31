#pragma once

using namespace std;

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
# include <stdlib.h>
#include <poll.h>
#include <algorithm>

struct ServerArgument {
public:
    int port;
	char *password;
};

ServerArgument parsingArgument(int argc, char *argv[]);
int setUpSocket(int port);