#include "../../header/Commands.hpp"

bool checkMask(vector<string> channels, Client client) {
    for (size_t i = 0; i < channels.size(); i++) {
        if (channels[i][0] != '#' && channels[i][0] != '&') {
            sendInfoClient(client, "<" + channels[i].substr(0, channels[i].length() - 1) + "> :Bad Channel Mask");
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
    if (command.size() < 2)
        return parsedCommand;

    channels = split(command[1], ',');
    if (command.size() == 3) {
        keys = split(command[2], ',');
        if (keys.size() > channels.size())
            return parsedCommand;
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

void joinCommand(string commandInput, Client *client, Server *server) {
    map<string, string> command = parseCommand(commandInput, *client);
    if (command.size() < 1) { return ; }
    for (map<string, string>::iterator it = command.begin(); it != command.end(); it++) {
        if (joinChannel(*client, server->getChannel(it->first), it->second) != -1) {
            continue;
        }
        else if (createChannel(*client, server, it->first, it->second)) {
            continue;
        }
    }
}

bool createChannel(Client client, Server *server, string name, string password) {
    if (server->getChannel(name) != NULL) {
        cout << "Channel already exists" << endl;
        return false;
    }
    if (name.empty()) {
        cout << "Channel name is empty" << endl;
        return false;
    }
    Channel channel(name.substr(1), password);
    channel.addUser(client);
    channel.addOperator(client);
    server->addChannel(channel);
    sendInfoClient(client, ":" + client.getName() + " JOIN " + name + "\r\n");
    return true;
}

int joinChannel(Client client, Channel *channel, string password) {
    if (channel == NULL) {
        return -1;
    }
    if (channel->isUser(client)) {
        cout << "Already in channel" << endl;
        return false;
    }
    list<char> mode = channel->getMode();
    if (find(mode.begin(), mode.end(), 'k') != mode.end() && channel->getPassword() != password) {
        cout << "Wrong password" << endl;
        return false;
    }
    if (find(mode.begin(), mode.end(), 'i') != mode.end() && !channel->isInvited(client)) {
        cout << "Channel is invite only" << endl;
        return false;
    }
    if (channel->getClients().size() >= (size_t)channel->getMaxUsers()) {
        cout << "Channel is full" << endl;
        return false;
    }
    channel->addUser(client);
    sendInfoClient(client, ":" + client.getName() + " JOIN #" + channel->getName() + "\r\n");
    sendInfoClient(client, "<" + channel->getName() + "> :" + channel->getTopic() + \
        "\n Members :");
    channel->displayChannelMembers();
    return true;
}