#include "../header/Commands.hpp"

void commandHub(string commandInput, Client client, Server server) {
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
