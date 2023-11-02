#include "../../header/Commands.hpp"

void inviteCommand(string commandInput, Client *client, Server *server) {
    if (client == NULL) {
        return ;
    }
    vector<string> command = initCommand(commandInput);
    if (command.size() > 3) {
        return ;
    }
    if (command.size() < 3) {
        client->addCmdToSend(ERR_NEEDMOREPARAMS(string(""), string("INVITE")));
        return ;
    }
    Channel *channel = server->getChannel(command[2].substr(1));
    if (channel == NULL) {
        client->addCmdToSend(ERR_NOSUCHCHANNEL(client->getName(), command[2].substr(1)));
        return ;
    }
    Client *receiver = server->getClient(command[1]);
    if (receiver == NULL) {
        client->addCmdToSend(ERR_NOSUCHNICK(command[1]));
        return ;
    }
    if (!inviteClient(client, *receiver, channel)) {
        return ;
    }
    client->addCmdToSend(RPL_INVITING(client->getName(), receiver->getName(), channel->getName()));
    receiver->addCmdToSend(":" + client->getName() + " INVITE " + receiver->getName() + " #" + channel->getName() + "\r\n");
}

bool inviteClient(Client *sender, Client receiver, Channel *channel) {
    if (!channel->isUser(*sender)) {
        sender->addCmdToSend(ERR_NOTONCHANNEL(channel->getName(), sender->getName()));
        return false;
    }
    if (channel->isUser(receiver)) {
        sender->addCmdToSend(ERR_USERONCHANNEL(channel->getName(), receiver.getName()));
        return false;
    }
    if (!channel->isOperator(*sender)){
        sender->addCmdToSend(ERR_CHANOPRIVSNEEDED(channel->getName(), sender->getName()));
        return false;
    }
    if (channel->getClients().size() >= (size_t)channel->getMaxUsers()) {
        return false;
    }
    channel->addInvited(receiver);
    return true;
}