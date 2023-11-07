#include "../../header/Commands.hpp"
#include "../../header/Channel.hpp"

void printVector(vector<string> command) {
    for (size_t i = 0; i < command.size(); i++) {
        cout << command[i] << endl;
    }
}

/*---------------------------------------- Parsing Command ----------------------------------------*/
bool checkIfChannel(string channel) {
    if (channel[0] != '#') {
        return false;
    }
    return true;
}

string concatMsg(vector<string> command) {
    string msg;
    msg += command[2].substr(1) + " ";
    for (size_t i = 3; i < command.size(); i++) {
        msg += command[i] + " ";
    }
    return msg;
}

int toChanOperator(string channel) {
    for (size_t i = 0; i < channel.size(); i++) {
        if (channel[i] == '@' || channel[i] == '%')
            i++;
        if (i > 3)
            return 0;
        if (channel[i] == '#')
            return i;
    }
    return 0;
}

int chanIndex(string channel, int ope) {
    if (channel[ope] == '#') {
        return ope + 1;
    }
    return 0;
}

/*---------------------------------------- PRIVMSG Command ----------------------------------------*/
void sendMessageCommand(string commandInput, Client * client, Server *server) {
    if (client == NULL)
        return ;
    vector<string> command = initCommand(commandInput);
    if (command.size() < 2 || commandInput.find(':') == string::npos) {
        client->addCmdToSend(ERR_NEEDMOREPARAMS(string(""), string("PRIVMSG")));
        return ;
    }
    int ope = toChanOperator(command[1]);
    int x = chanIndex(command[1], ope);
    if (x == 0)
        x += 1;
    Channel *channel = server->getChannel(command[1].substr(x));
    if (!channel->isUser(*client)) {
        client->addCmdToSend(ERR_NOTONCHANNEL(channel->getName(), client->getName()));
        return ;
    }
    Client *receiver = server->getClient(command[1]);
    if (channel == NULL && receiver == NULL) {
        client->addCmdToSend(ERR_NOSUCHNICK(command[1]));
        return ;
    }
    string msg = commandInput.substr(commandInput.find(':') + 1);
    if (channel != NULL) {
        if (ope == 0)
            sendMessage(server->getChannel(command[1].substr(1)), msg, server, client);
        else
            sendInfoChannelOperator(channel, PRIVMSGCHAN(client->getName(), channel->getName(), msg), server, client);
        return ;
    }
    else {
        sendPrivateMessage(client, server->getClient(command[1]), msg);
        return ;
    }
}

/*---------------------------------------- Send Message ------------------------------------------*/
bool sendPrivateMessage(Client *sender, Client *receiver , string message) {
    if (receiver == NULL)
        return false;
    receiver->addCmdToSend(PRIVMSGUSER(sender->getName(), sender->getName(), message));
    return true;
}

bool sendMessage(Channel *channel, string message, Server *server, Client *client) {
    sendInfoChannelOtherUsers(channel, PRIVMSGCHAN(client->getName(), channel->getName(), message), server, client);
    return true;
}

