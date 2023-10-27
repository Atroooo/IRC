#include "../../header/Commands.hpp"

/*---------------------------------------- Parsing Command ----------------------------------------*/
bool checkMask(vector<string> channels, Client client) {
    for (size_t i = 0; i < channels.size(); i++) {
        if (channels[i][0] != '#' && channels[i][0] != '&') {
            sendInfoClient(client, ERR_BADCHANMASK(channels[i].substr(0, channels[i].length() - 1)));
            return false;
        }
    }
    return true;
}

vector<string> split(string str, char delimiter) {
    vector<string> result;
    string tmp = "";

    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == delimiter) {
            result.push_back(tmp);
            tmp = "";
        }
        else
            tmp += str[i];
    }
    result.push_back(tmp);
    return result;
}

map<string, string> parseCommand(string Command, Client client) {
    map<string, string> parsedCommand;
    vector<string> command;
    vector<string> channels;
    vector<string> keys;

    if (Command.empty())
        return parsedCommand;

    char *cmd = strtok((char *)Command.c_str(), " ");
    while (cmd != NULL) {
        command.push_back(cmd);
        cmd = strtok(NULL, " ");
    }
    if (command.size() < 2) {
        sendInfoClient(client, ERR_NEEDMOREPARAMS(string("JOIN")));
        return parsedCommand;
    }

    channels = split(command[1], ',');
    if (command.size() == 3) {
        keys = split(command[2], ',');
        if (keys.size() > channels.size()) {
            sendInfoClient(client, "<JOIN> :Too many targets");
            return parsedCommand;
        }
    }
    if (checkMask(channels, client) == false)
        return parsedCommand;

    for (size_t i = 0; i < channels.size(); i++) {
        if (command.size() == 3) {
            if (i >= keys.size())
                parsedCommand[channels[i]] = "";
            else
                parsedCommand[channels[i]] = keys[i];
        }
        else
            parsedCommand[channels[i]] = "";
    }
    return parsedCommand;
}

string removeENDL(string str) {
    if (str[str.length() - 1] == '\n')
        str = str.substr(0, str.length() - 1);
    return str;
}

/*---------------------------------------- Join and Create Command ---------------------------------*/
void joinCommand(string commandInput, Client *client, Server *server) {
    if (commandInput == "JOIN 0") {
        //leave all channels
        return ;
    }
    map<string, string> command = parseCommand(commandInput, *client);
    if (command.size() < 1) { return ; }
    for (map<string, string>::iterator it = command.begin(); it != command.end(); it++) {
        string name = removeENDL(it->first.substr(1, it->first.size() - 1));
        if (joinChannel(*client, server->getChannel(name), it->second) != -1) {
            continue;
        }
        else if (!createChannel(*client, server, name, it->second)) {
            break ;
        }
    }
}

/*---------------------------------------- Create Channel ----------------------------------------*/
//ADD MODE AND TOPIC USING SENDINFOCHANNEL
bool createChannel(Client client, Server *server, string name, string password) {
    if (server->getChannel(name.substr(1)) != NULL) {
        return false;
    }
    Channel channel(name, password);
    channel.addUser(client);
    channel.addOperator(client);
    server->addChannel(channel);
    sendInfoClient(client, JOINCHAN(client.getName(), name));
    sendInfoClient(client, RPL_NAMREPLY(client.getName(), name, channel.getChannelMembers()));
    return true;
}

/*---------------------------------------- Join Channel ----------------------------------------*/
int passCheck(Client client, Channel channel, string password) {
    if (channel.isUser(client)) {
        sendInfoClient(client, "<" + channel.getName()+  "> : Already in channel");
        return false;
    }
    list<char> mode = channel.getMode();
    if (find(mode.begin(), mode.end(), 'k') != mode.end() && channel.getPassword() != password) {
        sendInfoClient(client, ERR_BADCHANNELKEY(string("#" + channel.getName())));
        return false;
    }
    if (find(mode.begin(), mode.end(), 'i') != mode.end() && !channel.isInvited(client)) {
        sendInfoClient(client, ERR_INVITEONLYCHAN(string("#" + channel.getName())));
        return false;
    }
    if (channel.getClients().size() >= (size_t)channel.getMaxUsers()) {
        sendInfoClient(client, ERR_CHANNELISFULL(string("#" + channel.getName())));
        return false;
    }
    return true;
}

int joinChannel(Client client, Channel *channel, string password) {
    if (channel == NULL) {
        sendInfoClient(client, ERR_NOSUCHCHANNEL);
        return -1;
    }
    if (passCheck(client, *channel, password) == false) { return false; }    
    channel->addUser(client);
    sendInfoClient(client, JOINCHAN(client.getName(), channel->getName()));
    sendInfoClient(client, INFO_JOIN(channel->getName(), channel->getTopic(), channel->getMembers()));
    sendInfoChannel(*channel, JOINCHAN(client.getName(), channel->getName()));
    sendInfoClient(client, RPL_NAMREPLY(client.getName(), channel->getName(), channel->getChannelMembers()));
    return true;
}
