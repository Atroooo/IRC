#include "../../header/Commands.hpp"

void modeCommand(string commandInput, Client client, Server *server) {
    vector<string> command = initCommand(commandInput);
    vector<string> commandParameters;
    if (command.size() > 2 && !command[3].empty()) {
        commandParameters = initCommand(command[3]);
    }
    Channel *channel = server->getChannel(command[1].substr(1));
    if (channel == NULL) {
        sendInfoClient(client, ERR_NOSUCHCHANNEL(client.getName(), command[1].substr(1)));
        return ;
    }
    if (command.size() == 2) {
        list<char> mode = channel->getMode();
        stringstream ss;
        ss << "+";
        for (list<char>::iterator it = mode.begin(); it != mode.end(); it++) {
            ss << *it;
        }
        sendInfoClient(client, RPL_CHANNELMODEIS(channel->getName(), ss.str()));
        sendInfoClient(client, RPL_CREATIONTIME(channel->getName(), client.getName(), channel->getCreationTime()));
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
        char mode = command[2][i];
        if (mode != 'i' && mode != 'k' && mode != 'l' && mode != 't' && mode != 'o' ) {
            sendInfoClient(client, ERR_UNKNOWNMODE(channel->getName(), client.getName(), mode));
        }
        else {
            if (mode == 'o') {
                if (commandParameters.size() == 0) {
                    sendInfoClient(client, ERR_NEEDMOREPARAMS(channel->getName(), string("MODE")));
                }
                else if (AddOrRemove == '+') {
                    promoteClient(client, server->getClient(command[3]), channel);
                    commandParameters.erase(command    cout << password << endl;
rameters.begin());
                }
                else {
                    demoteClient(client, server->getClient(command[3]), channel);
                    commandParameters.erase(commandParameters.begin());
                }
            }
            else if (mode == 'k') {
                if (commandParameters.size() == 0) {
                    sendInfoClient(client, ERR_NEEDMOREPARAMS(channel->getName(), string("MODE")));
                }
                else if (AddOrRemove == '+') {
                    if (!channel->isModeSet(mode)){
                        channel->setMode(mode);
                    }
                    channel->setPassword(commandParameters[0]);
                    commandParameters.erase(commandParameters.begin());
                    sendInfoChannel(*channel, ":" + client.getName() + " MODE #" + channel->getName() + " +" + mode + " " + channel->getPassword() + "\r\n");
                }
                else {
                    if (channel->isModeSet(mode)){
                        channel->unsetMode(mode);
                    }
                    channel->setPassword("");
                    commandParameters.erase(commandParameters.begin());
                    sendInfoChannel(*channel, ":" + client.getName() + " MODE #" + channel->getName() + " -" + mode + " " + channel->getPassword() + "\r\n");
                }
            }
            else if (mode == 'l') {
                if (commandParameters.size() == 0) {
                    sendInfoClient(client, ERR_NEEDMOREPARAMS(channel->getName(), string("MODE")));
                }
                else if (AddOrRemove == '+') {
                    channel->setMaxUsers(atoi(commandParameters[0].c_str()));
                    commandParameters.erase(commandParameters.begin());
                    sendInfoChannel(*channel, ":" + client.getName() + " MODE #" + channel->getName() + " +" + mode + " " + toString(channel->getMaxUsers()) + "\r\n");
                }
                else {
                    channel->setMaxUsers(10);
                    commandParameters.erase(commandParameters.begin());
                    sendInfoChannel(*channel, ":" + client.getName() + " MODE #" + channel->getName() + " -" + mode + " " + toString(channel->getMaxUsers()) + "\r\n");
                }
            }
            else {
                if (!channel->isModeSet(mode)){
                    channel->setMode(mode);
                    sendInfoChannel(*channel, ":" + client.getName() + " MODE #" + channel->getName() + " +" + mode + "\r\n");
                }
            }
        }
        i++;
    }
}

bool changeMode(Client client, Channel *channel) {
    if (!channel->isUser(client)) {
        sendInfoClient(client, ERR_NOTONCHANNEL(channel->getName(), client.getName()));
        return false;
    }
    if (!channel->isOperator(client)) {
        sendInfoClient(client, ERR_CHANOPRIVSNEEDED(channel->getName(), client.getName()));
        return false;
    }
    return true;
}

bool promoteClient(Client sender, Client *receiver, Channel *channel) {
    if (receiver == NULL) {
        sendInfoClient(sender, ERR_NOSUCHNICK(sender.getName()));
        return false;
    }
    if (!channel->isUser(sender)) {
        sendInfoClient(sender, ERR_NOTONCHANNEL(channel->getName(), sender.getName()));
        return false;
    }
    if (!channel->isOperator(sender)) {
        sendInfoClient(sender, ERR_CHANOPRIVSNEEDED(channel->getName(), sender.getName()));
        return false;
    }
    if (!channel->isUser(*receiver)) {
        sendInfoClient(sender, ERR_USERNOTINCHANNEL(channel->getName(), sender.getName(), receiver->getName()));
        return false;
    }
    if (channel->isOperator(*receiver)) {
        return false;
    }
    channel->addOperator(*receiver);
    sendInfoChannel(*channel, ":" + sender.getName() + " MODE #" + channel->getName() + " +o " + receiver->getName() + "\r\n");
    return true;
}

bool demoteClient(Client sender, Client *receiver, Channel *channel) {
    if (receiver == NULL) {
        sendInfoClient(sender, ERR_NOSUCHNICK(sender.getName()));
        return false;
    }
    if (!channel->isUser(sender)) {
        sendInfoClient(sender, ERR_NOTONCHANNEL(channel->getName(), sender.getName()));
        return false;
    }
    if (!channel->isOperator(sender)) {
        sendInfoClient(sender, ERR_CHANOPRIVSNEEDED(channel->getName(), sender.getName()));
        return false;
    }
    if (!channel->isUser(*receiver)) {
        sendInfoClient(sender, ERR_USERNOTINCHANNEL(channel->getName(), sender.getName(), receiver->getName()));
        return false;
    }
    if (!channel->isOperator(*receiver)) {
        return false;
    }
    channel->removeOperator(*receiver);
    sendInfoChannel(*channel, ":" + sender.getName() + " MODE #" + channel->getName() + " -o " + receiver->getName() + "\r\n");
    return true;
}

string toString(int number) {
    stringstream ss;
    ss << number;
    return ss.str();
}