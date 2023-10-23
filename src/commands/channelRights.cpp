#include "../header/Commands.hpp"

void changeRightsCommand(string commandInput, Client sender, Server server) {
    (void) commandInput;
    vector<string> command;
    if (command.size() != 3) {
        cout << "Wrong input : /(de/pro)mote [channel] [user]" << endl;
        return ;
    }
    Channel *channel = server.getChannel(command[1]);
    Client *receiver = channel->getClient(command[2]);
    if (receiver == NULL) {
        cout << "User not found" << endl;
        return ;
    }
    if (command[0] == "/promote") {
        promoteClient(sender, *receiver, server.getChannel(command[1]));
        return ;
    }
    if (command[0] == "/demote") {
        demoteClient(sender, *receiver, server.getChannel(command[1]));
        return ;
    }
}

bool promoteClient(Client sender, Client receiver, Channel *channel) {
    if (!channel->isUser(sender)) {
        cout << "User not in channel" << endl;
        return false;
    }
    if (!channel->isOperator(sender)) {
        cout << "Operator rights required" << endl;
        return false;
    }
    channel->addOperator(receiver);
    return true;
}

bool demoteClient(Client sender, Client receiver, Channel *channel) {
    if (!channel->isUser(sender)) {
        cout << "User not in channel" << endl;
        return false;
    }
    if (!channel->isOperator(sender)) {
        cout << "Operator rights required" << endl;
        return false;
    }
    channel->removeOperator(receiver);
    return true;
}

