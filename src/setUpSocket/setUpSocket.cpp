#include "../../header/includes.hpp"

void	bindToSocket(int listening, int port){
	sockaddr_in servAddr;

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(port);
    
    if (bind(listening, (sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
		cerr << "Can't bind to IP/port" << endl;
        _exit(-1);
	}
}

void listenSocket(int listening){
    if (listen(listening, SOMAXCONN) < 0) {
        cerr << "Can't listen! Quitting" << endl;
        _exit(-1);
    }
}

int setUpSocket(int port) {
    int opt = -1;

    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd < 0) {
        cerr << "Error: socket() failed" << endl;
        exit(1);
    }

    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
        cerr << "Error: setsockopt() failed" << endl;
        exit(1);
    }

    if (fcntl(socketFd, F_SETFL, O_NONBLOCK) < 0) {
        cerr << "Error: fcntl() failed" << endl;
        exit(1);
    }

	bindToSocket(socketFd, port);
    listenSocket(socketFd);
    return socketFd;
}
