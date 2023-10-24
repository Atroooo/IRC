#include "../header/Commands.hpp"

void commandHub(string commandInput, Client client, Server *server) {
    stringstream ss(commandInput);
    string key;
    ss >> key;
    cout << "key: " << key << endl;
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
    if (key == "PROMOTE" || key == "DEMOTE") {
        changeRightsCommand(commandInput, client, server);
        return ;
    }
    // else {
    //     sendMessageCommand(commandInput, client, server);
    //     return ;
    // }
}

bool sendMessage(Client client, Channel *channel, string message) {
    if (message.empty()) {
        cout << "Message is empty" << endl;
        return false;
    }
    (void)channel, (void)client;
    //Send message to all users in channel
    //send(socket, buf, size, flag)
    return true;
}

bool sendPrivateMessage(Client client, string message) {
    if (message.empty()) {
        cout << "Message is empty" << endl;
        return false;
    }
    (void)client;
    //Send message to client
    return true;
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

bool channelMask(vector<string> command) {
    cout << command[1][0] << endl;
    if (command[1][0] != '#' && command[1][0] != '&') {
        cout << "<" << command[1].substr(1, command[1].length()) << "> :Bad Channel Mask" << endl;
        return false;
    }
    return true;
}