#include "../header/Commands.hpp"

void topicCommand(char *commandInput, Client client, Server server) {
    string delimiter = "#";
    vector<string> command = getCommand(commandInput, delimiter.c_str());
    if (command.size() != 3) {
        cout << "Wrong input : /topic [channel] [topic]" << endl;
        return ;
    }
    Channel *channel = server.getChannel(command[1]);
    if (channel == NULL) {
        cout << "Channel does not exist" << endl;
        return ;
    }
    if (!changeTopic(client, channel, command[2])) {
        cout << "Topic not changed" << endl;
        return ;
    }
    cout << "Topic changed" << endl;
}

bool changeTopic(Client client, Channel *channel, string topic) {
    if (!channel->isUser(client)) {
        cout << "User not in channel" << endl;
        return false;
    }
    if (!channel->isOperator(client)) {
        cout << "Operator rights required" << endl;
        return false;
    }
    channel->setTopic(topic);
    return true;
}
