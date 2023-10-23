#include "../header/Commands.hpp"

void commandHub(string commandInput, Client client, Server server) {
    if (commandInput.compare(0,4,"JOIN")) {
        joinCommand(commandInput, client, server);
        return ;
    }
    if (commandInput.compare(0,4,"PART")) {
        leaveCommand(commandInput, client, server);
        return ;
    }
    if (commandInput.compare(0,4,"TOPIC")) {
        topicCommand(commandInput, client, server);
        return ;
    }
    if (commandInput.compare(0,4,"MODE")) {
        modeCommand(commandInput, client, server);
        return ;
    }
    if (commandInput.compare(0,4,"INVITE")) {
        inviteCommand(commandInput, client, server);
        return ;
    }
    if (commandInput.compare(0,4,"KICK")) {
        kickCommand(commandInput, client, server);
        return ;
    }
    if (commandInput.compare(0,4,"PROMOTE") || commandInput.compare(0,4,"DEMOTE")) {
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
