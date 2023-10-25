#include "../../header/Commands.hpp"

void kickCommand(string commandInput, Client client, Server *server) {

    vector<string> command = initCommand(commandInput);
    if (command.size() != 3) {
        sendInfoClient(client, "<KICK> :Not enough parameters\r\n");
        cout << "<KICK> :Not enough parameters" << endl;
        return ;
    }
    if (channelMask(command) == false) {
        return ;
    }
    Channel *channel = server->getChannel(command[1].substr(1));
    if (channel == NULL) {
        sendInfoClient(client, "<" + command[1].substr(1) + "> :No such channel\r\n");
        cout << "<" << command[1].substr(1) << "> :No such channel" << endl;
        return ;
    }
    Client *receiver = server->getClient(command[2]);
    if (receiver == NULL) {
        sendInfoClient(client, "<" + command[2] + "> :No such nick\r\n");
        cout << "<" << command[2] << "> :No such nick" << endl;
        return ;
    }
    if (!kickClient(client, *receiver, channel)) {
        return ;
    }
    sendKickMessage(client, receiver, channel, command);
}

bool kickClient(Client sender, Client receiver, Channel *channel) {
    // send to sender in channel
    if (!channel->isUser(sender)) {
        sendInfoClient(sender, "<" + channel->getName() + "> :You're not on that channel\r\n");
        cout << "<" << channel->getName() << "> :You're not on that channel" << endl;
        return false;
    }
    // send to sender in channel
    if (!channel->isUser(receiver)) {
        sendInfoClient(sender, "<" + receiver.getName() + "><" + channel->getName() + ">  :They aren't on that channel\r\n");
        cout << "<" << receiver.getName() << "><"<< channel->getName() << "> :They aren't on that channel" << endl;
        return false;
    }
    // send to sender in channel
    if (!channel->isOperator(sender)) {
        sendInfoClient(sender, "<" + channel->getName() + "> :You're not channel operator\r\n");
        cout << "<" << channel->getName() << "> :You're not channel operator" << endl;
        return false;
    }
    channel->removeUser(receiver);
    return true;
}

void sendKickMessage(Client client, Client *receiver, Channel *channel, vector<string> command) {

    //send to all users in channel
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