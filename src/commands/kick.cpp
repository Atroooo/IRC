#include "../../header/Commands.hpp"

void kickCommand(string commandInput, Client *client, Server *server) {

    if (client == NULL) {
        return ;
    }
    vector<string> command = initCommand(commandInput);
    if (channelMask(command, client) == false) {
        return ;
    }
    Channel *channel = server->getChannel(command[1].substr(1));
    if (channel == NULL) {
        return ;
    }
    Client *receiver = server->getClient(command[2]);
    if (receiver == NULL) {
        client->addCmdToSend(ERR_NOSUCHNICK(command[1].substr(1), channel->getName()));
        return ;
    }
    if (command.size() < 3) {
        client->addCmdToSend(ERR_NEEDMOREPARAMS(client->getName(), channel->getName(), string("KICK")));
        return ;
    }
    if (!kickClient(client, *receiver, channel)) {
        return ;
    }
    if (commandInput.find(':') != string::npos) {
        string msg = commandInput.substr(commandInput.find(':') + 1);
        sendInfoChannel(channel, ":" + client->getName() + " KICK #" + channel->getName() + " " + receiver->getName() + " " + client->getName() +  " " + msg + "\r\n", server);
        receiver->addCmdToSend(":" + client->getName() + " KICK #" + channel->getName() + " " + receiver->getName() + " " + client->getName() + " " + msg + "\r\n");
    }
    else {
        sendInfoChannel(channel, ":" + client->getName() + " KICK #" + channel->getName() + " " + receiver->getName() + " " + client->getName() + "\r\n", server);
        receiver->addCmdToSend(":" + client->getName() + " KICK #" + channel->getName() + " " + receiver->getName() + " " + client->getName() + "\r\n");
    }
    serverLog("Kick ", receiver->getName() + " kicked from " + channel->getName() + " by " + client->getName(), GREEN);
}

bool kickClient(Client *sender, Client receiver, Channel *channel) {
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
    channel->removeUser(receiver);
    return true;
}