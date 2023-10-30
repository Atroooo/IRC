#include "../../header/includes.hpp"

#define ALREADY_CONNECTED  0
#define WRONG_LOGIN_DATA  1
#define FIRST_CONNECTION  2
#define NOT_ALL_DATA 3
#define GOT_ALL_DATA 4

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

int checkPassAndNick(char *buf, int clientSocket, Server *server, char *serverPassword){
    string bufStr = string(buf);
    if (bufStr.find("PASS") == string::npos)
        return NOT_ALL_DATA;
    if (bufStr.find("NICK") == string::npos)
        return NOT_ALL_DATA;
    int connectionStatus = checkIfUserConnected(buf, clientSocket, server, serverPassword);
    if (connectionStatus == WRONG_LOGIN_DATA)
        return ( WRONG_LOGIN_DATA);
    // else if (connectionStatus == FIRST_CONNECTION){
    //     return (FIRST_CONNECTION);
    // }
    if (bufStr.find("USER") == string::npos)
        return NOT_ALL_DATA;
    return GOT_ALL_DATA;
}

int clientAction(int clientSocket, char *serverPassword, Server *server){
    string finalBuf;
    int bytesReceived;
    while (true){
        char buf[1028];
        memset(buf, 0, 1028);
        bytesReceived = recv(clientSocket, buf, 1027, MSG_DONTWAIT);
        finalBuf += buf;   
        cout << endl << endl << buf << endl << endl;
        if (bytesReceived == 0){
            cerr << "Client disconnected" << endl;
            return FALSE;
        }
        if (server->getClient(clientSocket) != NULL) break;
        int allDataParsed = checkPassAndNick((char *)finalBuf.c_str(), clientSocket, server, serverPassword);
        if (allDataParsed == GOT_ALL_DATA) break;
        if (allDataParsed == WRONG_LOGIN_DATA) return false;
    }
    if (strncmp(finalBuf.c_str(), "QUIT", 4) == 0){
        cout << "Client disconnected " << endl;
        return (FALSE);
    }
    if (bytesReceived == -1){
        cerr << "Error in recv(). Quitting" << endl;
        exit(1);
    }
    // cout << "BUF = " << buf << endl;
    commandHub(finalBuf.c_str(), server->getClient(clientSocket), server);
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