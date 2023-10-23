#include "../../header/includes.hpp"
#include <cstddef>
#include <cstring>
#include <sys/poll.h>


int clientAction(int clientSocket, char *serverPassword, Server *server){
	char buf[4096];

    memset(buf, 0, 4096);

    // Wait for client to send data
    int bytesReceived = recv(clientSocket, buf, 4095, 0);
    if (bytesReceived == -1)
    {
        cerr << "Error in recv(). Quitting" << endl;
        //NEED EXIT
    }
    if (bytesReceived == 0 || strncmp(buf, "QUIT", 4) == 0)
    {
        cout << "Client disconnected " << endl;
        return (FALSE);
    }
    buf[bytesReceived] = '\0';
    // Echo message back to client
    if (checkPassword(buf, serverPassword) == false){
        return FALSE;
    }
    cout << "Received: " << string(buf, 0, bytesReceived) << endl;
    if (buf[0] == '\0')
        return (TRUE);
    Client client(getSubStrBuffer(buf, (char *)"NICK "), clientSocket);
    // NEED TO DELETE NAME IN DESTRUCTOR CLIENT
    server->addClient(client);
    commandHub(buf, client, *server);
    int x = send(clientSocket, buf, bytesReceived + 1, 0);
    if (x < 0) {
        cerr << "Error in send(). Quitting" << endl;
        //NEED EXIT
    }
    return (TRUE);
}

void checkClient(Server *server, char *serverPassword) {
    if (server->getFdsList().size() == 1) {
        return;
    }
    for (size_t i = server->getServChanCount(); i < server->getFdsList().size(); i++) {
        if (server->getFd(i)->revents == POLLIN) {
            if (clientAction(server->getFd(i)->fd, serverPassword, server) == FALSE) {
                close(server->getFd(i)->fd);
                list<pollfd>::iterator it = server->getFdsList().begin();
                advance(it, i); // Move the iterator to the 'i'-th element
                server->getFdsList().erase(it); // Erase the 'i'-th element
                i--;
            }
        }
	}
}