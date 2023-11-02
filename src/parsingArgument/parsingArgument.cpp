#include "../../header/includes.hpp"

bool isAllDigits(const std::string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

void checkPortError(int port){
	if (port == 0){
		serverLog("Port ", "Port can't be 0", BLUE);
		_exit(-1);
	}
	if (port > 65535 || port <= -1){
		serverLog("Port ", "Port must be between 1 and 65535", BLUE);
		_exit(-1);
	}
}

void argumentCheckError(int argc, char *argv[]){
	if (argc != 3)
    {
        serverLog("Usage ", "./ircserv [port] [password]", BLUE);
        _exit(-1);
    }
    if (isAllDigits(argv[1]) == false){
        serverLog("Port ", "Port must be a number", BLUE);
        _exit(-1);
    }
}

ServerArgument parsingArgument(int argc, char *argv[]){
	argumentCheckError(argc, argv);
	ServerArgument serverArgument;
	serverArgument.port = atoi(argv[1]);
	serverArgument.password = argv[2];
	checkPortError(serverArgument.port);
	return serverArgument;
}