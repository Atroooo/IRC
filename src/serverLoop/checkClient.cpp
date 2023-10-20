#include "../../header/includes.hpp"
#include "../../header/typedef.hpp"
#include <cstring>



int clientAction(int clientSocket, char *serverPassword){
	char buf[4096];

    memset(buf, 0, 4096);

    // Wait for client to send data
    int bytesReceived = recv(clientSocket, buf, 4095, 0);
    if (bytesReceived == -1)
    {
        cerr << "Error in recv(). Quitting" << endl;
        //NEED EXIT
    }
    if (bytesReceived == 0)
    {
        cout << "Client disconnected " << endl;
        return (FALSE);
    }
    buf[bytesReceived] = '\0';
    // Echo message back to client
    
    if (checkPassword(buf, serverPassword) == false){
        return FALSE;
    }
    int x = send(clientSocket, buf, bytesReceived + 1, 0);
    if (x < 0) {
        cerr << "Error in send(). Quitting" << endl;
        //NEED EXIT
    }
    return (TRUE);
}

void checkClient(Server server, char *serverPassword) {
    if (server.getFdsVec().size() == 1) {
        return;
    }
    for (size_t i = server.getServChanCount(); i < server.getFdsVec().size(); i++) {
        if (server.getFd(i).revents == POLLIN) {
            if (clientAction(server.getFd(i).fd, serverPassword) == FALSE) {
                close(server.getFd(i).fd);
                server.getFdsVec().erase(server.getFdsVec().begin() + i);
                i--;
            }
        }
	}
}