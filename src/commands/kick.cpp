#include "../../header/Commands.hpp"

void kickCommand(string commandInput, Client *client, Server *server) {

    vector<string> command = initCommand(commandInput);
    if (channelMask(command, client) == false || command.size() >= 3) {
        return ;
    }
    Channel *channel = server->getChannel(command[1].substr(1));
    if (channel == NULL) {
        return ;
    }
    Client *receiver = server->getClient(command[2]);
    if (receiver == NULL) {
        client->addCmdToSend(ERR_NOSUCHNICK(command[1].substr(1)));
        return ;
    }
    if (command.size() < 3) {
        client->addCmdToSend(ERR_NEEDMOREPARAMS(channel->getName(), string("KICK")));
        return ;
    }
    if (!kickClient(client, *receiver, channel, server)) {
        return ;
    }
    sendInfoChannel(channel, ":" + client->getName() + " KICK #" + channel->getName() + " " + receiver->getName() + " " + client->getName() + "\r\n", server);
    receiver->addCmdToSend(":" + client->getName() + " KICK #" + channel->getName() + " " + receiver->getName() + " " + client->getName() + "\r\n");
}

bool kickClient(Client *sender, Client receiver, Channel *channel, Server * server) {
    if (!channel->isUser(*sender)) {
        sender->addCmdToSend(ERR_NOTONCHANNEL(channel->getName(), sender->getName()));
        return false;
    }
    if (!channel->isUser(receiver)) {
        sender->addCmdToSend(ERR_USERNOTINCHANNEL(channel->getName(), sender->getName(), receiver.getName()));
        return false;
    }
    if (!channel->isOperator(*sender)) {
        sender->addCmdToSend(ERR_CHANOPRIVSNEEDED(channel->getName(), sender->getName()));
        return false;
    }
    leaveChannel(&receiver, channel, "Kicked by " + sender->getName(), server);
    return true;
}