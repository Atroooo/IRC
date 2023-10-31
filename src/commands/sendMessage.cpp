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
    for (size_t i = 2; i < command.size(); i++) {
        msg += command[i] + " ";
    }
    return msg;
}

/*---------------------------------------- PRIVMSG Command ----------------------------------------*/
void sendMessageCommand(string CommandInput, Client client, Server *server) {
    vector<string> command = initCommand(CommandInput);
    if (command.size() < 2) {
        sendInfoClient(client, ERR_NEEDMOREPARAMS(string(""), string("PRIVMSG")));
        return ;
    }
    string message = concatMsg(command);
    if (checkIfChannel(command[1])) {
        sendMessage(client, server->getChannel(command[1].substr(1)), message);
        return ;
    }
    else {
        sendPrivateMessage(client, server->getClient(command[1]), message);
        return ;
    }
}

/*---------------------------------------- Send Message ------------------------------------------*/
bool sendPrivateMessage(Client sender, Client *receiver , string message) {
    if (receiver == NULL)
        return false;
    sendInfoClient(*receiver, PRIVMSGUSER(sender.getName(), receiver->getName(), message));
    return true;
}

bool sendMessage(Client client, Channel *channel, string message) {
    (void) client;
    if (channel == NULL)
        return false;
    // sendInfoChannel(*channel, PRIVMSGCHAN(channel->getName(), message));
    map<string, Client> clients = channel->getClients();
    for (map<string, Client>::iterator it = clients.begin(); it != clients.end(); it++) {
        if (it->second.getFd() != client.getFd()) {
            sendInfoClient(it->second, PRIVMSGCHAN(channel->getName(), message));
        }
    }
    return true;
}

/*---------------------------------------- Send Info -------------------------------------------*/
void checkRetSend(int ret) {
    if (ret < 0) {
        cerr << "Error in send(). Quitting" << endl;
        //NEED EXIT
    }
}

void sendInfoClient(Client client, string msg) {
    int ret = send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
    checkRetSend(ret);
}

void sendInfoChannel(Channel channel, string msg) {
    map<string, Client> members = channel.getClients();
    for (map<string, Client>::iterator it = members.begin(); it != members.end(); it++) {
        sendInfoClient(it->second, msg);
    }
}