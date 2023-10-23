#include "../header/Commands.hpp"

void leaveCommand(vector<string> command, Client client, Server server) {
    if (command.size() < 2) {
        cout << "<" << command[0] << "> : Not enough parameters" << endl;
        return ;
    }
    for (size_t i = 1; i < command.size(); i++) {
        Channel *channel = server.getChannel(command[i].substr(1));
        string message = "";
        if (channel == NULL) {
            cout << "<" << command[i] << "> : No such channel" << endl;
            return ;
        }
        if (leaveChannel(client, channel, message) == false) {
            cout << "Error leaving channel" << endl;
            return ;
        }
        cout << "Left channel " << channel->getName() << endl;
    }
}

bool leaveChannel(Client client, Channel *channel, string msg) {
    if (!channel->isUser(client)) {
        cout << "<" << channel->getName() << "> : You're not on that channel" << endl;
        return false;
    }
    if (!msg.empty()) {
        sendMessage(client, channel, "User " + client.getName() + " leaving channel #" + channel->getName() \
            + "with the message \""+  msg + "\".");
    }
    else {
        sendMessage(client, channel, "User " + client.getName() + " leaving channel #" + channel->getName() + ".");
    }
    channel->removeUser(client);
    return true;
}