
#include "../header/includes.hpp"
#include "../header/typedef.hpp"

int createSocket(){
	int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        _exit(-1);
    }
	return listening;
}

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

int serverLoop(int clientSocket){
	char buf[4096];

    memset(buf, 0, 4096);

    // Wait for client to send data
    int bytesReceived = recv(clientSocket, buf, 4095, 0);
    if (bytesReceived == -1)
    {
        cerr << "Error in recv(). Quitting" << endl;
    }
    if (bytesReceived == 0)
    {
        cout << "Client disconnected " << endl;
        return (FALSE);
    }
    buf[bytesReceived] = '\0';
    cout << string(buf, 0, bytesReceived) << endl;
    // Echo message back to client
    int x = send(clientSocket, buf, bytesReceived + 1, 0);
    if (x < 0) {
        cerr << "Error in send(). Quitting" << endl;
    }
    return (TRUE);
}

int argumentError(int argc){

    if (argc != 3)
    {
        cerr << "Usage: ./ircserv <port> <password>" << endl;
        _exit(-1);
    }
    return (0);
}

int main(int argc, char *argv[])
{
    // Check the command line arguments
    argumentError(argc);
    // Create a socket
	int listening = createSocket();
    // Bind the ip address and port to a socket
	bindToSocket(listening, atoi(argv[1]));
    // Tell Winsock the socket is for listening
    listenSocket(listening);
    // poll
    vector<struct pollfd> fds;
    struct pollfd listenerFd, newFd;
    listenerFd.fd = listening;
    listenerFd.events = POLLIN;
    listenerFd.revents = 1;
    fds.push_back(listenerFd);
    while (true) {
        int opt = poll(fds.data(), (nfds_t) fds.size(), TIMEOUT);
        if (opt < 0) {
            herror("poll");
            _exit(-1);
        }
        for (size_t i = 0; i < 1; i++) {
            if (fds[0].revents == POLLIN) {
                int clientSocket = waitClientConnection(fds[i].fd);
                newFd.fd = clientSocket;
                newFd.events = POLLIN;
                fds.push_back(newFd);
            }
        }
        for (size_t i = 1; i < fds.size(); i++) {
            if (fds[i].revents == POLLIN) {
                std::cout << "New message from client " << i << std::endl;
                if (serverLoop(fds[i].fd) == FALSE) {
                    close(fds[i].fd);
                    fds.erase(fds.begin() + i);
                    i--;
                }
            }
        }
    }
    return 0;
}
