#include "../../header/Commands.hpp"

void sendMessageCommand(string CommandInput, Client client, Server *server) {
    vector<string> command = initCommand(CommandInput);
    if (command.size() < 2) {
        cout << "<PRIVMSG> :Not enough parameters" << endl;
        return ;
    }
    (void) server, (void) client;
}

bool sendMessage(Client client, Channel *channel, string message) {
    int ret = 0;
    if (message.empty()) {
        ret = send(client.getFd(), "Message is empty", 17, 0);
        checkRetSend(ret);
        return false;
    }
    map<string, Client> clients = channel->getClients();
    for (map<string, Client>::iterator it = clients.begin(); it != clients.end(); it++) {
        if (it->second.getFd() != client.getFd()) {
            ret = send(it->second.getFd(), message.c_str(), message.length(), 0);
            checkRetSend(ret);
        }
    }
    return true;
}

bool sendPrivateMessage(Client sender, Client receiver , string message) {
    int ret = 0;
    if (message.empty()) {
        ret = send(sender.getFd(), "Message is empty", 17, 0);
        checkRetSend(ret);
        return false;
    }
    message = "PRIVMSG " + sender.getName() + " : " + message;
    ret = send(receiver.getFd(), message.c_str(), message.length(), 0);
    checkRetSend(ret);
    return true;
}

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
