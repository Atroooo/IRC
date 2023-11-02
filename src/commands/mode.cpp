#include "../../header/Commands.hpp"

void modeCommand(string commandInput, Client *client, Server *server) {

    if (client == NULL)
        return ;
    vector<string> command = initCommand(commandInput);
    vector<string> commandParameters;
    for (size_t i = 3; i < command.size(); i++) {
        if (command.size() > 2 && !command[i].empty())
            commandParameters.push_back(command[i]);
    }
    Channel *channel = server->getChannel(command[1].substr(1));
    if (channel == NULL) {
        client->addCmdToSend(ERR_NOSUCHCHANNEL(client->getName(), command[1].substr(1)));
        return ;
    }
    if (command.size() == 2) {
        list<char> mode = channel->getMode();
        stringstream ss;
        ss << "+";
        for (list<char>::iterator it = mode.begin(); it != mode.end(); it++) {
            ss << *it;
        }
        client->addCmdToSend(RPL_CHANNELMODEIS(channel->getName(), ss.str()));
        client->addCmdToSend(RPL_CREATIONTIME(channel->getName(), client->getName(), channel->getCreationTime()));
        return ;
    }
    char AddOrRemove = command[2][0];
    if (AddOrRemove != '+' && AddOrRemove != '-') {
        return ;
    }
    if (!changeMode(client, channel)) {
        return ;
    }
    size_t i = 1;
    while (i < command[2].size()) {
        char mode = command[2]
[i];
        if (mode != 'i' && mode != 'k' && mode != 'l' && mode != 't' && mode != 'o' ) {
            client->addCmdToSend(ERR_UNKNOWNMODE(channel->getName(), client->getName(), mode));
        }
        else {
            if (mode == 'o') {
                if (commandParameters.size() == 0) {
                    client->addCmdToSend(ERR_NEEDMOREPARAMS(channel->getName(), string("MODE")));
                }
                else if (AddOrRemove == '+') {
                    promoteClient(client, server->getClient(command[3]), channel, server);
                    commandParameters.erase(commandParameters.begin());
                    serverLog("Mode ", client->getName() + " promoted " + command[3] + " to operator in " + channel->getName(), GREEN);
                }
                else {
                    demoteClient(client, server->getClient(command[3]), channel, server);
                    commandParameters.erase(commandParameters.begin());
                    serverLog("Mode ", client->getName() + " demoted " + command[3] + " in " + channel->getName(), RED);
                }
            }
            else if (mode == 'k') {
                if (commandParameters.size() == 0) {
                    client->addCmdToSend(ERR_NEEDMOREPARAMS(channel->getName(), string("MODE")));
                }
                else if (AddOrRemove == '+') {
                    if (!channel->isModeSet(mode)){
                        channel->setMode(mode);
                    }
                    channel->setPassword(commandParameters[0]);
                    commandParameters.erase(commandParameters.begin());
                    sendInfoChannel(channel, ":" + client->getName() + " MODE #" + channel->getName() + " +" + mode + " " + channel->getPassword() + "\r\n", server);
                    serverLog("Mode ", client->getName() + " set password " + channel->getPassword() + " in " + channel->getName(), GREEN);
                }
                else {
                    if (channel->isModeSet(mode)){
                        channel->unsetMode(mode);
                    }
                    channel->setPassword("");
                    commandParameters.erase(commandParameters.begin());
                    sendInfoChannel(channel, ":" + client->getName() + " MODE #" + channel->getName() + " -" + mode + " " + channel->getPassword() + "\r\n", server);
                    serverLog("Mode ", client->getName() + " removed password in " + channel->getName(), RED);
                }
            }
            else if (mode == 'l') {
                if (commandParameters.size() == 0) {
                    client->addCmdToSend(ERR_NEEDMOREPARAMS(channel->getName(), string("MODE")));
                }
                else if (AddOrRemove == '+') {
                    channel->setMaxUsers(atof(commandParameters[0].c_str()));
                    commandParameters.erase(commandParameters.begin());
                    sendInfoChannel(channel, ":" + client->getName() + " MODE #" + channel->getName() + " +" + mode + " " + toString(channel->getMaxUsers()) + "\r\n", server);
                    serverLog("Mode ", client->getName() + " set max users to " + toString(channel->getMaxUsers()) + " in " + channel->getName(), GREEN);
                }
                else {
                    channel->setMaxUsers(10);
                    commandParameters.erase(commandParameters.begin());
                    sendInfoChannel(channel, ":" + client->getName() + " MODE #" + channel->getName() + " -" + mode + " " + toString(channel->getMaxUsers()) + "\r\n", server);
                    serverLog("Mode ", client->getName() + " removed max users in " + channel->getName(), RED);
                }
            }
            else {
                if (AddOrRemove == '+') {
                    if (!channel->isModeSet(mode)){
                        channel->setMode(mode);
                        sendInfoChannel(channel, ":" + client->getName() + " MODE #" + channel->getName() + " +" + mode + "\r\n", server);
                        serverLog("Mode ", client->getName() + " set mode " + mode + " in " + channel->getName(), GREEN);
                    }
                }
                else {
                    if (channel->isModeSet(mode)){
                        channel->unsetMode(mode);
                        sendInfoChannel(channel, ":" + client->getName() + " MODE #" + channel->getName() + " -" + mode + "\r\n", server);
                        serverLog("Mode ", client->getName() + " removed mode " + mode + " in " + channel->getName(), RED);
                    }
                }
            }
        }
        i++;
    }
}

bool changeMode(Client * client, Channel *channel) {
    if (!channel->isUser(*client)) {
        client->addCmdToSend(ERR_NOTONCHANNEL(channel->getName(), client->getName()));
        return false;
    }
    if (!channel->isOperator(*client)) {
        client->addCmdToSend(ERR_CHANOPRIVSNEEDED(channel->getName(), client->getName()));
        return false;
    }
    return true;
}

bool promoteClient(Client *sender, Client *receiver, Channel *channel, Server *server) {
    if (receiver == NULL) {
        sender->addCmdToSend(ERR_NOSUCHNICK(sender->getName()));
        return false;
    }
    if (!channel->isUser(*sender)) {
        sender->addCmdToSend(ERR_NOTONCHANNEL(channel->getName(), sender->getName()));
        return false;
    }
    if (!channel->isOperator(*sender)) {
        sender->addCmdToSend(ERR_CHANOPRIVSNEEDED(channel->getName(), sender->getName()));
        return false;
    }
    if (!channel->isUser(*receiver)) {
        sender->addCmdToSend(ERR_USERNOTINCHANNEL(channel->getName(), sender->getName(), receiver->getName()));
        return false;
    }
    if (channel->isOperator(*receiver)) {
        return false;
    }
    channel->addOperator(*receiver);
    sendInfoChannel(channel, ":" + sender->getName() + " MODE #" + channel->getName() + " +o " + receiver->getName() + "\r\n", server);
    return true;
}

bool demoteClient(Client *sender, Client *receiver, Channel *channel, Server *server) {
    if (receiver == NULL) {
        sender->addCmdToSend(ERR_NOSUCHNICK(sender->getName()));
        return false;
    }
    if (!channel->isUser(*sender)) {
        sender->addCmdToSend(ERR_NOTONCHANNEL(channel->getName(), sender->getName()));
        return false;
    }
    if (!channel->isOperator(*sender)) {
        sender->addCmdToSend(ERR_CHANOPRIVSNEEDED(channel->getName(), sender->getName()));
        return false;
    }
    if (!channel->isUser(*receiver)) {
        sender->addCmdToSend(ERR_USERNOTINCHANNEL(channel->getName(), sender->getName(), receiver->getName()));
        return false;
    }
    if (!channel->isOperator(*receiver)) {
        return false;
    }
    channel->removeOperator(*receiver);
    sendInfoChannel(channel, ":" + sender->getName() + " MODE #" + channel->getName() + " -o " + receiver->getName() + "\r\n", server);
    return true;
}

string toString(int number) {
    stringstream ss;
    ss << number;
    return ss.str();
}