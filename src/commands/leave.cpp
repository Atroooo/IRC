#include "../../header/Commands.hpp"

void leaveCommand(string commandInput, Client client, Server *server) {
    
    vector<string> command = initCommand(commandInput);
    if (command.size() < 1) {
        sendInfoClient(client, ERR_NEEDMOREPARAMS(string(""), string("PART")));
        return ;
    }
    vector<string> channelToLeave;
    split(command[1], ',', channelToLeave);
    vector<string>::iterator it = channelToLeave.begin();
    for (; it != channelToLeave.end(); it++) {
        if (it->find('#') == string::npos) {
            sendInfoClient(client, ERR_BADCHANMASK((*it).substr(1)));
            continue ;
        }
        Channel *channel = server->getChannel((*it).substr(1));
        if (channel == NULL) {
            sendInfoClient(client, ERR_NOSUCHCHANNEL(client.getName(), (*it).substr(1)));
            continue ;
        }
        if (!leaveChannel(client, channel, commandInput.substr(commandInput.find(':') + 1))) {
            continue ;
        }
    }
}

bool leaveChannel(Client client, Channel *channel, string msg) {
    if (!channel->isUser(client)) {
        sendInfoClient(client, ERR_NOTONCHANNEL(channel->getName(), client.getName()));
        return false;
    }
    sendInfoChannel(*channel, ":" + client.getName() + " PART #" + channel->getName() + " :" + msg + "\r\n");
    channel->removeUser(client);
    return true;
}

vector<string> split(string str, char delimiter, vector<string> &result) {
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}