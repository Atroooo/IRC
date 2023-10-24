#include "../header/Commands.hpp"

void inviteCommand(string commandInput, Client client, Server *server) {
    vector<string> command = initCommand(commandInput);
    if (command.size() != 3) {
        cout << "<INVITE> :Not enough parameters" << endl;
        return ;
    }
    Channel *channel = server->getChannel(command[1]);
    if (channel == NULL) {
        cout << "Channel does not exist" << endl;
        return ;
    }
    Client *receiver = server->getClient(command[2]);
    if (receiver == NULL) {
        cout << "<" << command[2] << "> :No such nick/channel" << endl;
        return ;
    }
    if (!inviteClient(client, *receiver, channel)) {
        return ;
    }
    cout << "<" << channel->getName() << "> <" << command[2] << ">" << endl;
}

bool inviteClient(Client sender, Client receiver, Channel *channel) {
    if (!channel->isUser(sender)) {
        cout << "<" << sender.getName() << "> :You're not on that channel" << endl;
        return false;
    }
    if (channel->isUser(receiver)) {
        cout << "User already in channel" << endl;
        cout << "<" << receiver.getName() << "> <"<< channel->getName() << "> :is already on channel" << endl;
        return false;
    }
    list<char> mode = channel->getMode();
    if (find(mode.begin(), mode.end(), 'i') != mode.end() && !channel->isOperator(sender)) {
        cout << "Operator rights required" << endl;
        cout << "<" << channel->getName() << "> :You're not channel operator" << endl;
        return false;
    }
    if (channel->getUsers().size() >= (size_t)channel->getMaxUsers()) {
        return false;
    }
    channel->addInvited(receiver);
    return true;
}
// err 301
// "<nick> :<away message>"