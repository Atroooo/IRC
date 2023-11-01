#include "../header/bot.hpp"
#include <netinet/in.h>
#include <sys/socket.h>

void	bindToSocket(int socketId, int port){
	sockaddr_in serverAddress;
    char *serverName = (char *)"127.0.0.1";
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    
    struct hostent *host = gethostbyname(serverName);
		if (host == NULL) {
			std::cerr << "Error during the resolution of server address" << std::endl;
			_exit(-1);
		}
	memcpy(&serverAddress.sin_addr.s_addr, host->h_addr, host->h_length);
    if (connect(socketId, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
    {
        cerr << "Can't listen! Quitting" << endl;
        _exit(-1);
    }
}

int setUpSocket(int port){
	int socketId = socket(AF_INET, SOCK_STREAM, 0);
    if (socketId == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        _exit(-1);
    }
	bindToSocket(socketId, port);
	return socketId;
}
