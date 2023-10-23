#include "../header/Commands.hpp"

void kickCommand(string command, Client client, Server server) {
    if (command.size() != 3) {
        cout << "Wrong input : /kick [channel] [user]" << endl;
        return ;
    }
    Channel *channel = server.getChannel(command[1]);
    if (channel == NULL) {
        cout << "Channel does not exist" << endl;
        return ;
    }
    Client *receiver = server.getClient(command[2]);
    if (!kickClient(client, *receiver, channel)) {
        cout << "User not kicked" << endl;
        return ;
    }
    cout << "User kicked" << endl;
}

bool kickClient(Client sender, Client receiver, Channel *channel) {
    if (!channel->isUser(sender) || !channel->isUser(receiver)) {
        cout << "User not in channel" << endl;
        return false;
    }
    if (!channel->isOperator(sender)) {
        cout << "Operator rights required" << endl;
        return false;
    }
    channel->removeUser(receiver);
    return true;
}
