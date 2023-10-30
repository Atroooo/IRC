#include "../../header/Commands.hpp"

// verifier presence de # devant channel
vector<string> getCommand(string commandInput) {
    vector<string> command;
    string cmd;

    cmd = commandInput.substr(0, commandInput.find(" ")); 
    command.push_back(cmd);
    cmd = commandInput.substr(commandInput.find(" ") + 1);
    command.push_back(cmd);
    return command;
}

string getMessage(string commandInput) {
    string message = commandInput.substr(commandInput.find(":") + 1);
    if (message.empty())
        return "";
    return message;
}

void leaveCommand(string commandInput, Client client, Server *server) {
    vector<string> command = getCommand(commandInput);
    Channel *channel;
    string message;

    if (command.size() < 1) {
        cout << "<PART> : Not enough parameters" << endl;
        return ;
    }
    message = getMessage(command[1]);
    if (!message.empty())
        channel = server->getChannel(command[1].substr(1, command[1].find(":") - 1));
    else
        channel = server->getChannel(command[1].substr(1));
    if (channel == NULL) {
        cout << "<" << command[1].substr(1, command[1].size() - 1) << "> : No such channel" << endl;
        return ;
    }
    if (leaveChannel(client, channel, message) == false) {
        cout << "Error leaving channel" << endl;
        return ;
    }
}

bool leaveChannel(Client client, Channel *channel, string msg) {
    if (!channel->isUser(client)) {
        cout << "<" << channel->getName() << "> : You're not on that channel" << endl;
        return false;
    }
    (void)msg;
    // if (msg == "") {
    //     sendMessage(client, channel, "User " + client.getName() + " leaving channel #" + channel->getName() 
    //         + "with the message \""+  msg + "\".");
    // }
    // else {
    //     sendMessage(client, channel, "User " + client.getName() + " leaving channel #" + channel->getName() + ".");
    // }
    channel->removeUser(client);
    return true;
}