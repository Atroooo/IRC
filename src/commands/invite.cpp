#include "../../header/Commands.hpp"

void inviteCommand(string commandInput, Client client, Server *server) {
    vector<string> command = initCommand(commandInput);
    if (command.size() != 3) {
        sendInfoClient(client, "<INVITE> :Not enough parameters\r\n");
        cout << "<INVITE> :Not enough parameters" << endl;
        return ;
    }
    Channel *channel = server->getChannel(command[1].substr(1));
    if (channel == NULL) {
        sendInfoClient(client, "<" + command[1] + "> :Channel does not exist\r\n");
        cout << "Channel does not exist" << endl;
        return ;
    }
    Client *receiver = server->getClient(command[2]);
    if (receiver == NULL) {
        sendInfoClient(client, "<" + command[2] + "> :No such nick/channel\r\n");
        cout << "<" << command[2] << "> :No such nick/channel" << endl;
        return ;
    }
    if (!inviteClient(client, *receiver, channel)) {
        return ;
    }
    // to all users in channel
    sendInfoClient(client, "<" +  channel->getName() + "><" + command[2] + ">\r\n");
    cout << "<" << channel->getName() << "> <" << command[2] << ">" << endl;
}

bool inviteClient(Client sender, Client receiver, Channel *channel) {
    if (!channel->isUser(sender)) {
        sendInfoClient(sender, "<" + sender.getName() + "> :You're not on that channel\r\n");
        cout << "<" << sender.getName() << "> :You're not on that channel" << endl;
        return false;
    }
    if (channel->isUser(receiver)) {
        sendInfoClient(sender, "<" + receiver.getName() + "><" + channel->getName() + "> :is already on channel\r\n");
        cout << "<" << receiver.getName() << "> <"<< channel->getName() << "> :is already on channel" << endl;
        return false;
    }
    list<char> mode = channel->getMode();
    if (find(mode.begin(), mode.end(), 'i') != mode.end() && !channel->isOperator(sender)) {
        sendInfoClient(sender, "<" + channel->getName() + "> :You're not channel operator\r\n");
        cout << "<" << channel->getName() << "> :You're not channel operator" << endl;
        return false;
    }
    if (channel->getClients().size() >= (size_t)channel->getMaxUsers()) {
        return false;
    }
    channel->addInvited(receiver);
    return true;
}
// err 301
// "<nick> :<away message>"