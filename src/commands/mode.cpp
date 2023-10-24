#include "../../header/Commands.hpp"

void modeCommand(string commandInput, Client client, Server *server) {
    (void) commandInput;
    vector<string> command;
    if (command.size() != 3) {
        cout << "Wrong input : /mode [channel] [mode]" << endl;
        return ;
    }
    Channel *channel = server->getChannel(command[1]);
    if (channel == NULL) {
        cout << "Channel does not exist" << endl;
        return ;
    }
    if (!changeMode(client, channel, command[2][0])) {
        cout << "Mode not changed" << endl;
        return ;
    }
    cout << "Mode changed" << endl;
}

bool changeMode(Client client, Channel *channel, char mode) {
    if (!channel->isUser(client)) {
        cout << "User not in channel" << endl;
        return false;
    }
    if (!channel->isOperator(client)) {
        cout << "Operator rights required" << endl;
        return false;
    }
    if (mode != 'i' || mode != 'k' || mode != 'l' || mode != 't' || mode != 'o' ) {
        cout << "Mode not supported by channel" << endl;
        return false;
    }
    channel->setMode(mode);
    return true;
}