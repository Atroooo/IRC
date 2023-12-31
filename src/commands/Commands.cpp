#include "../../header/Commands.hpp"

string stringToUpper(string strToConvert) {
    transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);
    return strToConvert;
}

void commandHub(string commandInput, Client *client, Server *server) {
    if (client == NULL)
        return ;
    if (client->getPassCheck() == false || client->getName() == "" || client->getUsername() == "") {
        serverLog("Client", " not registered", RED);
        return ;
    }
    else if (client->getIsRegistered() == false) {
        serverLog("Client " + client->getName(), " is registered.", GREEN);
        client->setIsRegistered(true);
    }
    stringstream ss(commandInput);
    string key;
    ss >> key;
    key = stringToUpper(key);
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
    if (key == "PRIVMSG") {
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