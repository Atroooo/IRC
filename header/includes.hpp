
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



struct ServerArgument {
public:
    int port;
	char *password;
};

//parsing
ServerArgument parsingArgument(int argc, char *argv[]);

using namespace std;
