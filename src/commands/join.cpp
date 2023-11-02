#include "../../header/Commands.hpp"

/*---------------------------------------- Parsing Command ----------------------------------------*/
bool checkMask(vector<string> channels, Client *client) {
    for (size_t i = 0; i < channels.size(); i++) {
        if (channels[i][0] != '#' && channels[i][0] != '&') {
            client->addCmdToSend(ERR_BADCHANMASK(channels[i].substr(0, channels[i].length() - 1)));
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

map<string, string> parseCommand(string Command, Client *client) {
    map<string, string> parsedCommand;
    vector<string> command;
    vector<string> channels;
    vector<string> keys;

    if (Command.empty() || Command.size() <= 8)
        return parsedCommand;

    char *cmd = strtok((char *)Command.c_str(), " ");
    while (cmd != NULL) {
        command.push_back(cmd);
        cmd = strtok(NULL, " ");
    }
    if (command.size() < 2) {
        client->addCmdToSend(ERR_NEEDMOREPARAMS(command[1], string("JOIN")));
        return parsedCommand;
    }

    channels = split(command[1], ',');
    if (command.size() == 3) {
        keys = split(command[2], ',');
        if (keys.size() > channels.size()) {
            client->addCmdToSend("<JOIN> :Too many targets");
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

string getName(string name) {
    string retName = "";
    int i = 1;

    while (name[i]) {
        if (name[i] >= 31 && name[i] <= 126)
            retName += name[i];
        i++;
    }
    return retName;
}

string removeEndofLine(string password) {
    string retPassword = "";
    int i = 0;

    while (password[i] && password[i] != '\r' && password[i] != '\n') {
        if (password[i] >= 31 && password[i] <= 126)
            retPassword += password[i];
        i++;
    }
    return retPassword;
}

/*---------------------------------------- Join and Create Command ---------------------------------*/
void joinCommand(string commandInput, Client *client, Server *server) {
    if (client == NULL) {
        return ;
    }
    if (removeEndofLine(commandInput) == "JOIN 0") {
        leaveAllChannels(client, server);
        return ;
    }
    map<string, string> command = parseCommand(commandInput, client);
    if (command.size() < 1) { return ; }
    for (map<string, string>::iterator it = command.begin(); it != command.end(); it++) {
        string password = removeEndofLine(it->second);
        string name = getName(it->first);
        if (joinChannel(client, server->getChannel(name), password, server) != -1) {
            continue;
        }
        else if (!createChannel(client, server, name, it->second)) {
            break ;
        }
    }
}

/*---------------------------------------- Create Channel ----------------------------------------*/
bool createChannel(Client *client, Server *server, string name, string password) {
    if (server->getChannel(name.substr(1)) != NULL) {
        return false;
    }
    Channel channel(name, password);
    channel.addUser(*client);
    channel.addOperator(*client);
    server->addChannel(channel);
    client->addCmdToSend(JOINCHAN(client->getName(), name));
    client->addCmdToSend(RPL_NAMREPLY(client->getName(), name, channel.getChannelMembers()));
    return true;
}

/*---------------------------------------- Join Channel ----------------------------------------*/
int passCheck(Client *client, Channel *channel, string password) {
    list<char> mode = channel->getMode();
    if (find(mode.begin(), mode.end(), 'k') != mode.end() && channel->getPassword() != password) {
        client->addCmdToSend(ERR_BADCHANNELKEY(string("#" + channel->getName())));
        return false;
    }
    if (find(mode.begin(), mode.end(), 'i') != mode.end() && !channel->isInvited(*client)) {
        client->addCmdToSend(ERR_INVITEONLYCHAN(string("#" + channel->getName())));
        return false;
    }
    if (channel->getClients().size() >= (size_t)channel->getMaxUsers()) {
        client->addCmdToSend(ERR_CHANNELISFULL(string("#" + channel->getName())));
        return false;
    }
    return true;
}

int joinChannel(Client *client, Channel *channel, string password, Server *server) {
    if (channel == NULL) {
        return -1;
    }
    if (passCheck(client, channel, password) == false) { return false; }    
    channel->addUser(*client);
    client->addCmdToSend(JOINCHAN(client->getName(), channel->getName()));
    client->addCmdToSend(INFO_JOIN(channel->getName(), channel->getTopic(), channel->getMembers()));
    sendInfoChannelOtherUsers(channel, JOINCHAN(client->getName(), channel->getName()), server, client);
    client->addCmdToSend(RPL_NAMREPLY(client->getName(), channel->getName(), channel->getChannelMembers()));
    return true;
}