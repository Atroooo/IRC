#include "../../header/Commands.hpp"

void modeCommand(string commandInput, Client client, Server *server) {
    vector<string> command = initCommand(commandInput);
    if (command.size() > 3) {
        return ;
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
    
    if (!changeMode(client, channel, command[2][0])) {
        cout << "Mode not changed" << endl;
        return ;
    }
    cout << "Mode changed" << endl;
}

bool changeMode(Client client, Channel *channel, char mode) {
    if (!channel->isUser(client)) {
        sendInfoClient(client, ERR_NOTONCHANNEL(channel->getName(), client.getName()));
        return false;
    }
    if (!channel->isOperator(client)) {
        sendInfoClient(client, ERR_CHANOPRIVSNEEDED(channel->getName(), client.getName()));
        return false;
    }
    if (mode != 'i' || mode != 'k' || mode != 'l' || mode != 't' || mode != 'o' ) {
        cout << "Mode not supported by channel" << endl;
        return false;
    }
    channel->setMode(mode);
    return true;
}

bool promoteClient(Client sender, Client receiver, Channel *channel) {
    if (!channel->isUser(sender)) {
        sendInfoClient(sender, ERR_NOTONCHANNEL(channel->getName(), sender.getName()));
        return false;
    }
    if (!channel->isOperator(sender)) {
        sendInfoClient(sender, ERR_CHANOPRIVSNEEDED(channel->getName(), sender.getName()));
        return false;
    }
    channel->addOperator(receiver);
    return true;
}

bool demoteClient(Client sender, Client receiver, Channel *channel) {
    if (!channel->isUser(sender)) {
        sendInfoClient(sender, ERR_NOTONCHANNEL(channel->getName(), sender.getName()));
        return false;
    }
    if (!channel->isOperator(sender)) {
        sendInfoClient(sender, ERR_CHANOPRIVSNEEDED(channel->getName(), sender.getName()));
        return false;
    }
    channel->removeOperator(receiver);
    return true;
}

