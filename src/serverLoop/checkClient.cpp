#include "../../header/includes.hpp"

#define ALREADY_CONNECTED  0
#define WRONG_PASSWORD  1
#define FIRST_CONNECTION  2

int checkIfUserConnected(char *buf, int clientSocket, Server *server, char *serverPassword){
    if (server->getClient(clientSocket) != NULL)
        return ALREADY_CONNECTED;
    (void)serverPassword;
    // if (checkPassword(buf, serverPassword) == false){
    //     return WRONG_PASSWORD;
    // }
    string nickname = getSubStrBuffer(buf, (char *)"NICK ");
    cout << nickname << " connected" << endl;
    Client client(nickname, clientSocket);
    server->addClient(client);
    // string botMessage = "Hello ";
    // botMessage.append(nickname);
    // int x = send(clientSocket, botMessage.c_str(), sizeof(botMessage), 0);
    // if (x < 0) {
    //     cerr << "Error in send(). Quitting" << endl;
    //     //NEED EXIT
    // }
    return FIRST_CONNECTION;
}

int clientAction(int clientSocket, char *serverPassword, Server *server){
	char buf[4096];
    memset(buf, 0, 4096);

    int bytesReceived = 0;
    cout << "before" << endl;
    bytesReceived = recv(clientSocket, buf, 4096, MSG_DONTWAIT);
    if (strncmp(buf, "QUIT", 4) == 0){
        cout << "Client disconnected " << endl;
        return (FALSE);
    }
    cout << "bytesReceived " << bytesReceived << endl;
    cout << buf << endl;
    // while (bytesReceived < 30){
    //     bytesReceived = recv(clientSocket, buf, 4096, MSG_DONTWAIT);
    //     if (strncmp(buf, "QUIT", 4) == 0){
    //         cout << "Client disconnected " << endl;
    //         return (FALSE);
    //     }
    //     if (server->getClient(clientSocket) != NULL){
    //         break ;
    //     }
    // }
    if (bytesReceived == -1){
        cerr << "Error in recv(). Quitting" << endl;
        exit(1);
    }
    buf[bytesReceived] = '\0';
    // if on le \n
    // int connectionStatus = checkIfUserConnected(buf, clientSocket, server, serverPassword);
    // if (connectionStatus == WRONG_PASSWORD)
    //     return (FALSE);
    // else if (connectionStatus == FIRST_CONNECTION){
    //     return (TRUE);
    // }
    // commandHub(buf, server->getClient(clientSocket), server);
    // // int x = send(clientSocket, buf, bytesReceived, 0);
    // botAction(buf, clientSocket, x);
    (void)server;
    (void)serverPassword;
    return (TRUE);
}

void checkClient(Server *server, char *serverPassword) {
    if (server->getFdsVector().size() == 1) {
        return;
    }
    for (size_t i = server->getServChanCount(); i < server->getFdsVector().size(); i++) {
        if (server->getFd(i)->revents == POLLIN) {
            if (clientAction(server->getFd(i)->fd, serverPassword, server) == FALSE) {
                close(server->getFd(i)->fd);
                vector<struct pollfd> vec = server->getFdsVector();
                vec.erase(vec.begin() + i);
                server->setVector(vec);
                i--;
            }
        }
	}
}