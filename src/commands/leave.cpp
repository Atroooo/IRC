#include "../header/Commands.hpp"

void leaveCommand(vector<string> command, Client client, Server server) {
    if (command.size() != 2) {
        cout << "Wrong input : /leave [Channel]" << endl;
        return ;
    }
    if (leaveChannel(client, server.getChannel(command[1])) == false) {
        cout << "Error leaving channel" << endl;
        return ;
    }
    cout << "Left channel " << command[1] << endl;
}

bool leaveChannel(Client Client, Channel *Channel) {
    if (!Channel->isUser(Client)) {
        cout << "User not in channel" << endl;
        return false;
    }
    Channel->removeUser(Client);
    return true;
}