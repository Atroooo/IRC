#include "../../header/includes.hpp"
#include "../../header/typedef.hpp"

int clientAction(int clientSocket){
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

void checkClient(vector<struct pollfd> & fds){
    if (fds.size() == 1)
        return;
	
    for (size_t i = 1; i < fds.size(); i++) {
		if (fds[i].revents == POLLIN) {
			if (fds[i].fd && clientAction(fds[i].fd) == FALSE) {
				close(fds[i].fd);
				fds.erase(fds.begin() + i);
				i--;
			}
		}
	}
}