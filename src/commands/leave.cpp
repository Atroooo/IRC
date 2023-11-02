#include "../../header/Commands.hpp"

void leaveCommand(string commandInput, Client *client, Server *server) {
    if (client == NULL) {
        return ;
    }
    vector<string> command = initCommand(commandInput);
    if (command.size() < 1) {
        client->addCmdToSend(ERR_NEEDMOREPARAMS(string(""), string("PART")));
        return ;
    }
    vector<string> channelToLeave;
    split(command[1], ',', channelToLeave);
    vector<string>::iterator it = channelToLeave.begin();
    for (; it != channelToLeave.end(); it++) {
        if (it->find('#') == string::npos) {
            client->addCmdToSend(ERR_BADCHANMASK((*it).substr(1)));
            continue ;
        }
        Channel *channel = server->getChannel((*it).substr(1));
        if (channel == NULL) {
            client->addCmdToSend(ERR_NOSUCHCHANNEL(client->getName(), (*it).substr(1)));
            continue ;
        }
        if (!leaveChannel(client, channel, commandInput.substr(commandInput.find(':') + 1), server))
            continue ;
        serverLog("Leave ", client->getName() + " left " + channel->getName(), GREEN);
    }
}

bool leaveChannel(Client *client, Channel *channel, string msg, Server * server) {
    if (client == NULL) {
        return false;
    }
    if (!channel->isUser(*client)) {
        client->addCmdToSend(ERR_NOTONCHANNEL(channel->getName(), client->getName()));
        return false;
    }
    sendInfoChannel(channel, ":" + client->getName() + " PART #" + channel->getName() + " :" + msg + "\r\n", server);
    channel->removeUser(*client);
    if (channel->isOperator(*client))
        channel->removeOperator(*client);
    return true;
}

void leaveAllChannels(Client *client, Server *server) {
    if (client == NULL) {
        return ;
    }
    list<Channel> channels = server->getChannel();
    for (list<Channel>::iterator it = channels.begin(); it != channels.end(); it++) {
        if (it->isUser(*client)) {
            leaveChannel(client, &(*it), "Leaving all channels", server);
        }
    }
    serverLog("Leave ", client->getName() + " left all channels", GREEN);
}

vector<string> split(string str, char delimiter, vector<string> &result) {
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}