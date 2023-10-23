#include "../header/Commands.hpp"

vector<string> getCommand(char *commandInput, const char *delimiter) {
    vector<string> command;
    
    if (commandInput == NULL || delimiter == NULL)
        return command;
    char *cmd = strtok(commandInput, delimiter); 
    while (cmd != NULL) {
        command.push_back(cmd);
        cmd = strtok(NULL, delimiter);
    }
    return command;
}

void commandHub(char *commandInput, Client client, Server server) {
    string delimiter = " ";
    vector<string> command = getCommand(commandInput, delimiter.c_str());
    if (command[0] == "JOIN") {
        joinCommand(commandInput, client, server);
        return ;
    }
    if (command[0] == "PART") {
        leaveCommand(commandInput, client, server);
        return ;
    }
    if (command[0] == "/topic") {
        topicCommand(commandInput, client, server);
        return ;
    }
    if (command[0] == "/mode") {
        modeCommand(commandInput, client, server);
        return ;
    }
    if (command[0] == "/invite") {
        inviteCommand(commandInput, client, server);
        return ;
    }
    if (command[0] == "/kick") {
        kickCommand(commandInput, client, server);
        return ;
    }
    if (command[0] == "/promote" || command[0] == "/demote") {
        changeRightsCommand(commandInput, client, server.getChannel(command[1]));
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
