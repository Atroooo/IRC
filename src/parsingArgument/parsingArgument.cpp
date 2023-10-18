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
		cerr << "Usage: Port number can't be less than 1" << endl;
		_exit(-1);
	}
	if (port > 65535 || port <= -1){
		cerr << "Usage: Port number can't be more than 65535" << endl;
		_exit(-1);
	}
}

void argumentCheckError(int argc, char *argv[]){
	if (argc != 3)
    {
        cerr << "Usage: ./ircserv <port> <password>" << endl;
        _exit(-1);
    }
    if (isAllDigits(argv[1]) == false){
        cerr << "Usage: Port must contain only digit" << endl;
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