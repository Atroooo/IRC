#include "../../header/includes.hpp"

#define ALREADY_CONNECTED  0
#define WRONG_LOGIN_DATA  1
#define FIRST_CONNECTION  2

bool checkIfNickNameAvailable(Server *server, string nickname){
    if (server->getClient(nickname)){
        cout << "Nickname already used" << endl;
        return false;
    }
    return true;
}

int checkIfUserConnected(char *buf, int clientSocket, Server *server, char *serverPassword){
    if (server->getClient(clientSocket) != NULL)
        return ALREADY_CONNECTED;
    if (checkPassword(buf, serverPassword) == false){
        return WRONG_LOGIN_DATA;
    }
    string nickname = getSubStrBuffer(buf, (char *)"NICK ");
    if (checkIfNickNameAvailable(server, nickname) == false){
        return WRONG_LOGIN_DATA;
    }
    Client client(nickname, clientSocket);
    server->addClient(client);
    return FIRST_CONNECTION;
}

bool checkPassAndNick(char *buf){
    string bufStr = string(buf);
    if (bufStr.find("PASS") == string::npos)
        return false;
    if (bufStr.find("NICK") == string::npos)
        return false;
    return true;
}

int clientAction(int clientSocket, char *serverPassword, Server *server){
	char buf[1028];
    memset(buf, 0, 1028);
    int bytesReceived;
    while (true){
        bytesReceived = recv(clientSocket, buf, 1028, MSG_DONTWAIT);    
        if (bytesReceived == 0){
            cerr << "Client disconnected" << endl;
            return FALSE;
        }
        if (server->getClient(clientSocket) != NULL) break;
        if (checkPassAndNick(buf) == true) break;
        usleep(100);
    }
    if (strncmp(buf, "QUIT", 4) == 0){
        cout << "Client disconnected " << endl;
        return (FALSE);
    }
    if (bytesReceived == -1){
        cerr << "Error in recv(). Quitting" << endl;
        exit(1);
    }
    cout << "BUF = " << buf << endl;
    int connectionStatus = checkIfUserConnected(buf, clientSocket, server, serverPassword);
    if (connectionStatus == WRONG_LOGIN_DATA)
        return (FALSE);
    else if (connectionStatus == FIRST_CONNECTION){
        return (TRUE);
    }
    commandHub(buf, server->getClient(clientSocket), server);
    //botAction(buf, clientSocket, x);

    return (TRUE);
}

void checkClient(Server *server, char *serverPassword) {
    if (server->getFdsList().size() == 1) {
        return;
    }
    for (size_t i = 1; i < server->getFdsList().size(); i++) {
        if (server->getFd(i)->revents == POLLIN) {
            if (clientAction(server->getFd(i)->fd, serverPassword, server) == FALSE) {
                close(server->getFd(i)->fd);
                list<pollfd>::iterator it = server->getFdsList().begin();
                advance(it, i);
                server->getFdsList().erase(it);
                i--;
            }
        }
	}
}