#include "../../header/Commands.hpp"

void printVector(vector<string> vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
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
        cout << "concat "<< command[i] << endl;
    }
    return msg;
}

/*---------------------------------------- PRIVMSG Command ----------------------------------------*/
void sendMessageCommand(string CommandInput, Client client, Server *server) {
    vector<string> command = initCommand(CommandInput);
    printVector(command);
    if (command.size() < 2) {
        // server->setCommandsToSend(client.getFd(), ERR_NEEDMOREPARAMS(string("PRIVMSG")));
        // sendInfoClient(client, ERR_NEEDMOREPARAMS(string("PRIVMSG")));
        return ;
    }
    string message = concatMsg(command);
    if (checkIfChannel(command[1])) {
        sendMessage(server->getChannel(command[1].substr(1)), message, server);
        return ;
    }
    else {
        sendPrivateMessage(client, server->getClient(command[1]), message, server);
        return ;
    }
}

/*---------------------------------------- Send Message ------------------------------------------*/
bool sendPrivateMessage(Client sender, Client *receiver , string message, Server *server) {
    if (receiver == NULL)
        return false;
    (void) sender;
    (void) server;
    cout << "PV " << message << endl;
    // server->setCommandsToSend(receiver->getFd(), PRIVMSGUSER(sender.getName(), receiver->getName(), message));
    // sendInfoClient(*receiver, PRIVMSGUSER(sender.getName(), receiver->getName(), message));
    return true;
}

bool sendMessage(Channel *channel, string message, Server *server) {
    if (channel == NULL)
        return false;
    // sendInfoChannel(*channel, PRIVMSGCHAN(channel->getName(), message));
    sendInfoChannel(*channel, PRIVMSGCHAN(channel->getName(), message), server);
    return true;
}

/*---------------------------------------- Send Info -------------------------------------------*/
void sendInfoChannel(Channel channel, string msg, Server *server) {
    (void) server;
    (void) msg;
    map<string, Client> members = channel.getClients();
    for (map<string, Client>::iterator it = members.begin(); it != members.end(); it++) {
        cout << "osef" << endl;
        // server->setCommandsToSend(it->second.getFd(), msg);
        // sendInfoClient(it->second, msg);
    }
}

void sendInfoClient(Client client, string msg) {
    int ret = send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
    checkRetSend(ret);
}
