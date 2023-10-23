#include "../header/Commands.hpp"

void kickCommand(string commandInput, Client client, Server *server) {

    vector<string> command = initCommand(commandInput);
    if (command.size() != 3) {
        cout << "<KICK> :Not enough parameters" << endl;
        return ;
    }
    if (channelMask(command) == false) {
        return ;
    }
    Channel *channel = server->getChannel(command[1].substr(1, command[1].length()));
    if (channel == NULL) {
        cout << "<" << command[1].substr(1, command[1].length()) << "> :No such channel" << endl;
        return ;
    }
    Client *receiver = server->getClient(command[2]);
    if (receiver == NULL) {
        cout << "<" << command[2] << "> :No such nick" << endl;
        return ;
    }
    if (!kickClient(client, *receiver, channel)) {
        return ;
    }
    sendKickMessage(client, receiver, channel, command);
}

bool kickClient(Client sender, Client receiver, Channel *channel) {
    if (!channel->isUser(sender)) {
        cout << "<" << channel->getName() << "> :You're not on that channel" << endl;
        return false;
    }
    if (!channel->isUser(receiver)) {
        cout << "<" << receiver.getName() << "><"<< channel->getName() << "> :They aren't on that channel" << endl;
        return false;
    }
    if (!channel->isOperator(sender)) {
        cout << "<" << channel->getName() << "> :You're not channel operator" << endl;
        return false;
    }
    channel->removeUser(receiver);
    return true;
}

void sendKickMessage(Client client, Client *receiver, Channel *channel, vector<string> command) {

    if (command[4][0] == ':'){
        command[4].erase(0, 1);
        size_t i = 4;
        string message = "";
        while (i < command.size()) {
            message += command[i];
            message += " ";
            i++;
        }
        sendMessage(client, channel, \
            "User " + client.getName() + " kicked user " + receiver->getName() \
            + " from channel #" + channel->getName() + " with the message \"" + message + "\".");
    }
    else
        sendMessage(client, channel, \
            "User " + client.getName() + " kicked user " + receiver->getName() \
            + " from channel #" + channel->getName() + ".");
}