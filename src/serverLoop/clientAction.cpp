#include "../../header/includes.hpp"

int clientAction(int clientSocket, char *serverPassword, Server *server) {
    char buf[1028];
    string finalBuf;
    int bytesReceived;
    
    Client *client = server->getClient(clientSocket);
    if (client == NULL)
        return (FALSE);
    while (true) {
        memset(buf, 0, sizeof(buf));
        bytesReceived = recv(clientSocket, buf, sizeof(buf), MSG_DONTWAIT);
        if (bytesReceived == -1)
            return TRUE;
        if (bytesReceived == 0){
            client->addCmdToSend(": QUIT :Leaving\n");
            return FALSE;
        }
        finalBuf += buf;
        if (client != NULL && checkEndOfLine(finalBuf))
            break;
    }
    if (passAllCheck(client, finalBuf, serverPassword, server) == FALSE)
        return (FALSE);
    finalBuf = removeEndofLine(finalBuf);
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