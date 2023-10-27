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
    Client *receiver = server->getClient(command[2]);
    if (receiver == NULL) {
        sendInfoClient(client, ERR_NOSUCHNICK(command[1].substr(1)));
        return ;
    }
    if (command.size() != 3) {
        sendInfoClient(client, ERR_NEEDMOREPARAMS(string("KICK")));
        return ;
    }
    if (!kickClient(client, *receiver, channel)) {
        return ;
    }
    // sendInfoChannel(channel, ":" + client.getName() + " KICK " + channel->getName() + " " + receiver->getName() + "\r\n");
}

bool kickClient(Client sender, Client receiver, Channel *channel) {
    if (!channel->isUser(sender)) {
        sendInfoClient(sender, ERR_NOTONCHANNEL(channel->getName(), sender.getName()));
        return false;
    }
    if (!channel->isUser(receiver)) {
        sendInfoClient(sender, ERR_USERNOTINCHANNEL(channel->getName(), sender.getName(), receiver.getName()));
        return false;
    }
    if (!channel->isOperator(sender)) {
        sendInfoClient(sender, ERR_CHANOPRIVSNEEDED(channel->getName(), sender.getName()));
        return false;
    }
    channel->removeUser(receiver);
    return true;
}
