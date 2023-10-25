#include "../../header/Commands.hpp"

void kickCommand(string commandInput, Client client, Server *server) {

    vector<string> command = initCommand(commandInput);
    if (channelMask(command) == false) {
        return ;
    }
    Channel *channel = server->getChannel(command[1].substr(1));
    if (channel == NULL) {
        return ;
    }
    if (command.size() != 3) {
        sendInfoClient(client, ": 461 KICK #" + channel->getName() + " :" + client.getName() + " kick: Not enough parameters\r\n");
        return ;
    }
    Client *receiver = server->getClient(command[2]);
    if (receiver == NULL) {
        return ;
    }
    if (!kickClient(client, *receiver, channel)) {
        return ;
    }
    sendKickMessage(client, receiver, channel, command);
}

bool kickClient(Client sender, Client receiver, Channel *channel) {
    cout << "here" << endl;
    if (!channel->isUser(sender)) {
        sendInfoClient(sender, ": 442 KICK #" + channel->getName() + " :" + sender.getName() + channel->getName() + ":You're not on that channel\r\n");
        return false;
    }
    if (!channel->isUser(receiver)) {
        sendInfoClient(sender, ": 441 KICK #" + channel->getName() + " :" + sender.getName() + " :" + receiver.getName() + " :They aren't on that channel\r\n");
        return false;
    }
    if (!channel->isOperator(sender)) {
        sendInfoClient(sender, ": 482 KICK #" + channel->getName() + " " + sender.getName() + channel->getName() + " :You're not channel operator\r\n");
        return false;
    }
    channel->removeUser(receiver);
    return true;
}

void sendKickMessage(Client client, Client *receiver, Channel *channel, vector<string> command) {

    // TOO DISPLaY TO ALL USERS IN CHANNEL
    if (command[4][0]) {
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