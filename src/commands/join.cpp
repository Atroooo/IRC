#include "../../header/Commands.hpp"

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

map<string, string> parseCommand(string Command) {
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
    map<string, string> command = parseCommand(commandInput);
    if (command.size() < 1) {
        cout << "Invalid command. Usage : /join <channel>{,<channel>} [<key>{,<key>}]" << endl;
        return ;
    }
    for (map<string, string>::iterator it = command.begin(); it != command.end(); it++) {
        if (joinChannel(*client, server->getChannel(it->first), it->second) != -1) {
            continue;
        }
        else if (createChannel(*client, server, it->first, it->second)) {
            continue;
        }
    }
}

bool createChannel(Client Client, Server *server, string name, string password) {
    if (server->getChannel(name) != NULL) {
        cout << "Channel already exists" << endl;
        return false;
    }
    if (name.empty()) {
        cout << "Channel name is empty" << endl;
        return false;
    }
    Channel channel(name, password);
    channel.addUser(Client);
    channel.addOperator(Client);
    server->addChannel(channel);
    cout << "Channel created" << endl;
    const char * msg = ":lcompieg  ";
    int ret = send(Client.getFd(), msg, strlen(msg) - 1, 0);
    checkRetSend(ret);
    return true;
}

int joinChannel(Client Client, Channel *Channel, string password) {
    if (Channel == NULL) {
        return -1;
    }
    if (Channel->isUser(Client)) {
        cout << "Already in channel" << endl;
        return false;
    }
    list<char> mode = Channel->getMode();
    if (find(mode.begin(), mode.end(), 'k') != mode.end() && Channel->getPassword() != password) {
        cout << "Wrong password" << endl;
        return false;
    }
    if (find(mode.begin(), mode.end(), 'i') != mode.end() && !Channel->isInvited(Client)) {
        cout << "Channel is invite only" << endl;
        return false;
    }
    if (Channel->getClients().size() >= (size_t)Channel->getMaxUsers()) {
        cout << "Channel is full" << endl;
        return false;
    }
    Channel->addUser(Client);
    cout << "Joined channel" << endl;
    return true;
}