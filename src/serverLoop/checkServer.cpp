#include "../../header/includes.hpp"
#include "../../header/typedef.hpp"


int waitClientConnection(int listening){
	sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
 
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
        cout << client.sin_port << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }
	return clientSocket;
}

void checkServer(pollfd & newFd, vector<struct pollfd> & fds){
	for (size_t i = 0; i < 1; i++) {
		if (fds[0].revents == POLLIN) {
			int clientSocket = waitClientConnection(fds[i].fd);
			newFd.fd = clientSocket;
			newFd.events = POLLIN;
			fds.push_back(newFd);
		}
	}
}