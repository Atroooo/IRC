#include "../../header/includes.hpp"
#include <sys/ioctl.h>

void	bindToSocket(int listening, int port){
	sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1){
		std::cerr << "Can't bind to IP/port" << std::endl;
        _exit(-1);
	}
}

void listenSocket(int listening){
    if (listen(listening, SOMAXCONN) == -1)
    {
        cerr << "Can't listen! Quitting" << endl;
        _exit(-1);
    }
}

int setUpSocket(int port){
	int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        _exit(-1);
    }
    int opt = 1;
    if (setsockopt(listening, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(int)) < 0)
    {
        perror("Erreur lors de la configuration de SO_REUSEADDR");
        exit(1);
    }
	bindToSocket(listening, port);
	listenSocket(listening);
	return listening;
}
