#include "../../header/includes.hpp"

bool checkIfNickNameAvailable(Server *server, string nickname){
    if (server->getClient(nickname)){
        cout << "Nickname already used" << endl;
        return false;
    }
    return true;
}

bool checkNickClient(Client *client, string bufStr, Server *server) {
    if (client->getName().empty()) {
        if (bufStr.find("NICK") != string::npos) {
            string nickname = getSubStrBuffer((char *)bufStr.c_str(), (char *)"NICK ");
            if (checkIfNickNameAvailable(server, nickname) == false) {
                server->removeClient(client->getFd());
                return false;
            }
            client->setName(nickname);
            return true;
        }
        return true;
    }
    return true;
}

bool checkPassClient(Client *client, string bufStr, char *serverPassword, Server * server) {
    if (client->getPassCheck() == false) {
        if (bufStr.find("PASS") != string::npos) {
            if (checkPassword((char *)bufStr.c_str(), serverPassword) == false) {
                server->removeClient(client->getFd());
                return false;
            }
            client->setPassCheck(true);
            return true;
        }
        return true;
    }
    return true;
}

bool checkEndOfLine(string bufStr){
    if (bufStr.find("\r\n") == string::npos)
        return false;
    return true;
}


int clientAction(int clientSocket, char *serverPassword, Server *server) {
    char buf[1028];
    string finalBuf;
    int bytesReceived;
    
    Client *client = server->getClient(clientSocket);
    while (true) {
        memset(buf, 0, sizeof(buf));
        bytesReceived = recv(clientSocket, buf, sizeof(buf), MSG_DONTWAIT);
        finalBuf += buf;
        if (bytesReceived == 0){
            return FALSE;
        }
        if (bytesReceived == -1) {
            int error = errno;
            if (error == EAGAIN || error == EWOULDBLOCK) {
                break;
            }
            else {
                cerr << "Error in recv(): " << strerror(error) << " (Error code: " << error << ")" << endl;
                _exit(-1);
            }
        }
        if (client != NULL && checkEndOfLine(finalBuf))
            break;
    }
    // cout << "Received: " << finalBuf << endl;
    if (checkPassClient(client, finalBuf, serverPassword, server) == false) {
        return (FALSE);
    }
    if (checkNickClient(client, finalBuf, server) == false){
        return (FALSE);
    }
    if (strncmp(finalBuf.c_str(), "QUIT", 4) == 0){
        return (FALSE);
    }
    if (!finalBuf.empty())
        commandHub(finalBuf.c_str(), client, server);
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