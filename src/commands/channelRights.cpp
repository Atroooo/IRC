#include "../header/Commands.hpp"

void changeRightsCommand(vector<string> command, Client sender, Client receiver, Channel *channel) {
    if (command[0] == "/promote") {
        promoteClient(sender, receiver, channel);
        return ;
    }
    if (command[0] == "/demote") {
        demoteClient(sender, receiver, channel);
        return ;
    }
}

bool promoteClient(Client sender, Client receiver, Channel *channel) {
    if (!channel->isUser(sender) || !channel->isUser(receiver)) {
        cout << "User not in channel" << endl;
        return false;
    }
    if (!channel->isOperator(sender)) {
        cout << "Operator rights required" << endl;
        return false;
    }
    channel->addOperator(receiver);
    return true;
}

bool demoteClient(Client sender, Client receiver, Channel *channel) {
    if (!channel->isUser(sender) || !channel->isUser(receiver)) {
        cout << "User not in channel" << endl;
        return false;
    }
    if (!channel->isOperator(sender)) {
        cout << "Operator rights required" << endl;
        return false;
    }
    channel->removeOperator(receiver);
    return true;
}

