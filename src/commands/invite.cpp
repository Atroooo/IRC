#include "../header/Commands.hpp"

void inviteCommand(string commandInput, Client client, Server *server) {
    (void) commandInput;
    vector<string> command;
    if (command.size() != 3) {
        cout << "Wrong input : /invite [channel] [user]" << endl;
        return ;
    }
    Channel *channel = server->getChannel(command[1]);
    if (channel == NULL) {
        cout << "Channel does not exist" << endl;
        return ;
    }
    Client *receiver = server->getClient(command[2]);
    if (!inviteClient(client, *receiver, channel)) {
        cout << "User not invited" << endl;
        return ;
    }
    cout << "User invited" << endl;
}

bool inviteClient(Client sender, Client receiver, Channel *channel) {
    if (!channel->isUser(sender)) {
        cout << "User not in channel" << endl;
        return false;
    }
    if (channel->isUser(receiver)) {
        cout << "User already in channel" << endl;
        return false;
    }
    list<char> mode = channel->getMode();
    if (find(mode.begin(), mode.end(), 'i') != mode.end() && !channel->isOperator(sender)) {
        cout << "Operator rights required" << endl;
        return false;
    }
    if (channel->getUsers().size() >= (size_t)channel->getMaxUsers()) {
        cout << "Channel is full" << endl;
        return false;
    }
    channel->addInvited(receiver);
    return true;
}