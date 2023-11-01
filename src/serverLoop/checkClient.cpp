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

int checkPassAndNick(string bufStr, int clientSocket, Server *server, char *serverPassword){
    if (bufStr.find("PASS") == string::npos)
        return NOT_ALL_DATA;
    if (bufStr.find("NICK") == string::npos)
        return NOT_ALL_DATA;
    int connectionStatus = checkIfUserConnected((char *)bufStr.c_str(), clientSocket, server, serverPassword);
    if (connectionStatus == WRONG_LOGIN_DATA)
        return ( WRONG_LOGIN_DATA);
    if (bufStr.find("USER") == string::npos)
        return NOT_ALL_DATA;
    // if (bufStr.find("\r\n") == string::npos)
    //         return false;
    return GOT_ALL_DATA;
}

bool checkEndOfLine(string bufStr){
    // (void)bufStr;
    if (bufStr.find("\r\n") == string::npos)
            return false;
    return true;
}

int clientAction(int clientSocket, char *serverPassword, Server *server){
    char buf[1028];
    string finalBuf;
    int bytesReceived;
    
    while (true) {
        memset(buf, 0, sizeof(buf));
        bytesReceived = recv(clientSocket, buf, sizeof(buf), MSG_DONTWAIT);
        finalBuf += buf;
        if (bytesReceived == 0){
            cerr << "Client disconnected" << endl;
            return FALSE;
        }
        if (bytesReceived == -1 && bytesReceived != EAGAIN && bytesReceived != EWOULDBLOCK) {
            int error = errno;
            if (error != 11) {
                cerr << "Error in recv(): " << strerror(error) << " (Error code: " << error << ")" << endl;
                _exit(-1);
            }

        }
        if (server->getClient(clientSocket) != NULL && checkEndOfLine(finalBuf))
            break;
        else{
            int allDataParsed = checkPassAndNick((char *)finalBuf.c_str(), clientSocket, server, serverPassword);
            if (allDataParsed == GOT_ALL_DATA) break;
            if (allDataParsed == WRONG_LOGIN_DATA) return false;
        }
    }
    if (strncmp(finalBuf.c_str(), "QUIT", 4) == 0){
        cout << "Client disconnected " << endl;
        return (FALSE);
    }
    cout << "BUF = " << finalBuf << endl;
    commandHub(finalBuf.c_str(), server->getClient(clientSocket), server);
    return (TRUE);
}

int checkClient(Server *server, char *serverPassword) {
    if (server->getFdsVector().size() == 1) {
        return (TRUE);
    }
    for (size_t i = 1; i < server->getFdsVector().size(); i++) {
        if (clientAction(server->getFd(i)->fd, serverPassword, server) == FALSE) {
            close(server->getFd(i)->fd);
            return (FALSE);
        }
	}
    return (TRUE);
}