#include "../../header/Commands.hpp"

void commandHub(string commandInput, Client *client, Server *server) {
    stringstream ss(commandInput);
    string key;
    ss >> key;
    if (key == "JOIN") {
        joinCommand(commandInput, client, server);
        return ;
    }
    if (key == "PART") {
        leaveCommand(commandInput, client, server);
        return ;
    }
    if (key == "TOPIC") {
        topicCommand(commandInput, client, server);
        return ;
    }
    if (key == "MODE") {
        modeCommand(commandInput, client, server);
        return ;
    }
    if (key == "INVITE") {
        inviteCommand(commandInput, client, server);
        return ;
    }
    if (key == "KICK") {
        kickCommand(commandInput, client, server);
        return ;
    }
    if (key == "PRIVMSG" || key == "NOTICE") {
        sendMessageCommand(commandInput, client, server);
        return ;
    }
}

vector<string> initCommand(string commandInput) {

    stringstream ss(commandInput);
    string command;
    vector<string> commandVector;
    while (ss >> command) {
        commandVector.push_back(command);
    }
    return commandVector;
}

bool channelMask(vector<string> command, Client *client) {
    if (command[1][0] != '#' && command[1][0] != '&') {
        client->addCmdToSend(ERR_BADCHANMASK(command[1].substr(1, command[1].length())));
        return false;
    }
    return true;
}
