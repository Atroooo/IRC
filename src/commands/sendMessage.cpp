#include "../../header/Commands.hpp"

void sendMessageCommand(string CommandInput, Client client, Server *server) {
    vector<string> command = initCommand(CommandInput);
    if (command.size() < 2) {
        cout << "<PRIVMSG> :Not enough parameters" << endl;
        return ;
    }
    if (channelMask(command) == false) {
        return ;
    }
    Channel *channel = server->getChannel(command[1]);
    if (channel == NULL) {
        return ;
    }
    if (command.size() < 3) {
        cout << "<PRIVMSG> :No message to send" << endl;
        return ;
    }
    size_t i = 2;
    string message = "";
    while (i < command.size()) {
        message += command[i];
        message += " ";
        i++;
    }
    if (!sendMessage(client, channel, message)) {
        return ;
    }
    cout << "<" << client.getName() << "> :" << message << endl;
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
