#include "../../header/includes.hpp"

bool hasEndOfLine(string buffer) {
    if (buffer.find("\n") != string::npos)
        return TRUE;
    return FALSE;
}

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
        cout << buf << endl;
        if (bytesReceived == -1) {
            return TRUE;
        }
        if (bytesReceived == 0){
            client->addCmdToSend(": QUIT :Leaving\n");
            return FALSE;
        }
        finalBuf += buf;
        if (hasEndOfLine(buf) == FALSE) {
            client->addToBuffer(buf);
        }
        if (client != NULL && checkEndOfLine(finalBuf))
            break;
    }
    client->getBuffer() = removeEndofLine(client->getBuffer());
    string commandInput = client->getBuffer();
    client->setBuffer("");
    commandInput.append(finalBuf);
    if (passAllCheck(client, commandInput, serverPassword, server) == FALSE)
        return (FALSE);
    commandInput = removeEndofLine(commandInput);
    if (!commandInput.empty())
        commandHub(commandInput.c_str(), client, server);
    
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