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
    vector<string> command;
    map<string, string> parsedCommand;

    char *cmd = strtok((char *)Command.c_str(), " ");
    while (cmd != NULL) {
        command.push_back(cmd);
        cmd = strtok(NULL, " ");
    }
    if (command.size() < 2)
        return parseCommand("");

    vector<string> channels = split(command[1], ',');
    vector<string> keys = split(command[2], ',');
    if (keys.size() > channels.size())
        return parseCommand("");
    for (size_t i = 0; i < channels.size(); i++) {
        if (keys[i].empty())
            keys[i] = "";
        parsedCommand[channels[i]] = keys[i];
    }
    return parsedCommand;
}

void joinCommand(string commandInput, Client client, Server server) {
    cout << "ICI" << endl << endl;
    map<string, string> command = parseCommand(commandInput);
    if (command.size() < 1) {
        cout << "Invalid command. Usage : /join <channel>{,<channel>} [<key>{,<key>}]" << endl;
        return ;
    }
    for (map<string, string>::iterator it = command.begin(); it != command.end(); it++) {
        if (joinChannel(client, server.getChannel(it->first), it->second)) 
            cout << "Joined channel" << endl;
        else if (!createChannel(client, server, it->first, it->second)) {
            cout << "Error creating channel" << endl;
            return ;
        } 
    }
}

bool createChannel(Client Client, Server server, string name, string password) {
    if (server.getChannel(name) != NULL) {
        cout << "Channel already exists" << endl;
        return false;
    }
    if (name.empty()) {
        cout << "Channel name is empty" << endl;
        return false;
    }
    Channel channel(name, password);
    channel.addUser(Client);
    return true;
}

bool joinChannel(Client Client, Channel *Channel, string password) {
    if (Channel == NULL) {
        return false;
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
    if (Channel->getUsers().size() >= (size_t)Channel->getMaxUsers()) {
        cout << "Channel is full" << endl;
        return false;
    }
    Channel->addUser(Client);
    return true;
}