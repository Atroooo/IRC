#include "../../header/Commands.hpp"

void topicCommand(string commandInput, Client client, Server *server) {

    vector<string> command = initCommand(commandInput);
    if (command.size() < 2) {
        cout << "<TOPIC> :Not enough parameters" << endl;
        sendInfoClient(client, "<TOPIC> :Not enough parameters\r\n");
        return ;
    }
    if (channelMask(command) == false) {
        sendInfoClient(client, "<" + command[1].substr(0, command[1].length()) + "> :Bad Channel Mask\r\n");
        return ;
    }
    Channel *channel = server->getChannel(command[1].substr(1));
    if (channel == NULL) {
        return ;
    }
    if (commandInput.find(':') == string::npos) {
        if (channel->getTopic() == "No topic") {
            sendInfoClient(client, "<" + channel->getName() + ">:" + channel->getTopic() + " is set\r\n");
            return ;
        }
        sendInfoClient(client, "Topic for <" + channel->getName() + "> is: " + channel->getTopic() + "\r\n");
        cout << "<" << channel->getName() << "> :" << channel->getTopic() << endl;
        return ;
    }
    if (!changeTopic(client, channel)) {
        return ;
    }
    cout << commandInput << endl;
    channel->setTopic(commandInput.substr(commandInput.find(':') + 1));
    sendInfoClient(client, ":" + std::string(SERVER_NAME) + "TOPIC " + client.getName() + " has changed the topic to :" + channel->getTopic() + "\r\n");
}

bool changeTopic(Client client, Channel *channel) {
    if (!channel->isUser(client)) {
        sendInfoClient(client, "<" + channel->getName() + "> :You're not on that channel\r\n");
        cout << "<" << channel->getName() << "> :You're not on that channel" << endl;
        return false;
    }
    if (!channel->isOperator(client)) {
        sendInfoClient(client, "<" + channel->getName() + "> :You're not channel operator\r\n");
        cout << "<" << channel->getName() << "> :You're not channel operator" << endl;
        return false;
    }
    // if (find(channel->getMode().begin(), channel->getMode().end(), 't') != channel->getMode().end()) {
    //     sendInfoClient(client, "<" + channel->getName() + "> :Channel doesn't support modes\r\n");
    //     cout << "<" << channel->getName() << "> :Channel doesn't support modes" << endl;
    //     return false;
    // }
    return true;
}
