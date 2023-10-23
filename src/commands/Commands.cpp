#include "../header/Commands.hpp"

vector<string> getCommand(char *commandInput) {
    vector<string> command;
    
    char *cmd = strtok(commandInput, " "); 
    while (cmd != NULL) {
        command.push_back(cmd);
        cmd = strtok(NULL, " ");
    }
    return command;
}

void commandHub(char *commandInput, Client client, Server server) {
    vector<string> command = getCommand(commandInput);
    if (command[0][0] == '/') {
        if (command[0] == "/join") {
            joinCommand(command, client, server);
            return ;
        }
        if (command[0] == "/leave") {
            leaveCommand(command, client, server);
            return ;
        }
        if (command[0] == "/topic") {
            topicCommand(command, client, server);
            return ;
        }
        if (command[0] == "/mode") {
            modeCommand(command, client, server);
            return ;
        }
        if (command[0] == "/invite") {
            inviteCommand(command, client, server);
            return ;
        }
        if (command[0] == "/kick") {
            kickCommand(command, client, server); //a modif
            return ;
        }
        if (command[0] == "/promote" || command[0] == "/demote") {
            changeRightsCommand(command, client, client, server.getChannel(command[1]));
            return ;
        }
        return ;
    }
    // else {
    //     sendMessageCommand(commandInput, client, server);
    //     return ;
    // }
}

bool sendMessage(string message, Channel Channel) {
    if (message.empty()) {
        cout << "Message is empty" << endl;
        return false;
    }
    (void)Channel;
    //Send message to all users in channel
    return true;
}

bool sendPrivateMessage(Client client, string message, Channel Channel) {
    if (message.empty()) {
        cout << "Message is empty" << endl;
        return false;
    }
    (void)Channel;
    (void)client;
    //Send message to client
    return true;
}
