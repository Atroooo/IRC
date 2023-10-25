#include "../../header/Commands.hpp"

void topicCommand(string commandInput, Client client, Server *server) {

    vector<string> command = initCommand(commandInput);
    if (command.size() < 2) {
        cout << "<TOPIC> :Not enough parameters" << endl;
        return ;
    }
    if (channelMask(command) == false) {
        return ;
    }
    Channel *channel = server->getChannel(command[1].substr(1));
    cout << "cmd: |" << command[1].substr(1) << "|" << endl;
    if (channel == NULL) {
        cout << "ICI" << endl;
        return ;
    }
    if (command.size() < 3) {
        if (channel->getTopic() == "") {
            cout << "<" << channel->getName() << "> :No topic is set" << endl;
            return ;
        }
        cout << "<" << channel->getName() << "> :" << channel->getTopic() << endl;
        return ;
    }
    size_t i = 2;
    string message = "";
    while (i < command.size()) {
        message += command[i];
        message += " ";
        i++;
    }
    if (!changeTopic(client, channel, message)) {
        return ;
    }
    cout <<  "<" << channel->getName() << "> :<" << command[2] << ">" << endl;
}

bool changeTopic(Client client, Channel *channel, string topic) {
    if (!channel->isUser(client)) {
        cout << "<" << channel->getName() << "> :You're not on that channel" << endl;
        return false;
    }
    if (!channel->isOperator(client)) {
        cout << "<" << channel->getName() << "> :You're not channel operator" << endl;
        return false;
    }
    if (find(channel->getMode().begin(), channel->getMode().end(), 't') != channel->getMode().end()) {
        cout << "<" << channel->getName() << "> :Channel doesn't support modes" << endl;
        return false;
    }
    channel->setTopic(topic);
    return true;
}
