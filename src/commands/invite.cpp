#include "../../header/Commands.hpp"

void inviteCommand(string commandInput, Client client, Server *server) {
    cout << "inviteCommand: " << commandInput << endl;
    vector<string> command = initCommand(commandInput);
    cout << "inviteCommand size: " << command.size() << endl;
    if (command.size() > 3) {
        return ;
    }
    if (command.size() < 3) {
        sendInfoClient(client, ERR_NEEDMOREPARAMS(string("INVITE")));
        return ;
    }
    Channel *channel = server->getChannel(command[2].substr(1));
    cout << "inviteCommand channel: " << command[2].substr(1) << endl;
    if (channel == NULL) {
        sendInfoClient(client, ERR_NOSUCHCHANNEL(client.getName(), command[2].substr(1)));
        return ;
    }
    Client *receiver = server->getClient(command[1]);
    if (receiver == NULL) {
        sendInfoClient(client, ERR_NOSUCHNICK(command[1]));
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
        sendInfoClient(sender, ERR_NOTONCHANNEL(channel->getName(), sender.getName()));
        return false;
    }
    if (channel->isUser(receiver)) {
        sendInfoClient(sender, ERR_USERONCHANNEL(channel->getName(), receiver.getName()));
        return false;
    }
    if (!channel->isOperator(sender)){
        sendInfoClient(sender, ERR_CHANOPRIVSNEEDED(channel->getName(), sender.getName()));
        return false;
    }
    list<char> mode = channel->getMode();
    if (find(mode.begin(), mode.end(), 'i') == mode.end()) {
        sendInfoClient(sender, ERR_INVITEONLYCHAN(channel->getName()));
        return false;
    }
    if (channel->getClients().size() >= (size_t)channel->getMaxUsers()) {
        return false;
    }
    channel->addInvited(receiver);
    return true;
}
