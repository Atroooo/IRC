#include "../../header/Commands.hpp"

void topicCommand(string commandInput, Client *client, Server *server) {

    if (client == NULL) {
        return ;
    }
    vector<string> command = initCommand(commandInput);
    if (command.size() < 2) {
        client->addCmdToSend(ERR_NEEDMOREPARAMS(string(""),string("TOPIC")));
        return ;
    }
    if (channelMask(command, client) == false) {
        client->addCmdToSend(ERR_BADCHANMASK(command[1].substr(1)));
        return ;
    }
    Channel *channel = server->getChannel(command[1].substr(1));
    if (channel == NULL) {
        client->addCmdToSend(ERR_NOSUCHCHANNEL(client->getName(), command[1].substr(1)));
        return ;
    }
    if (commandInput.find(':') == string::npos) {
        if (channel->getTopic() == "No topic") {
            client->addCmdToSend(RPL_NOTOPIC(channel->getName(), client->getName()));
            return ;
        }
        client->addCmdToSend(RPL_TOPIC(channel->getName(), client->getName(), channel->getTopic()));
        return ;
    }
    if (!changeTopic(client, channel)) {
        return ;
    }
    channel->setTopic(commandInput.substr(commandInput.find(':') + 1));
    sendInfoChannel(channel, RPL_TOPICWHOTIME(channel->getName(), client->getName(), get_time()), server);
    sendInfoChannel(channel, RPL_TOPIC(channel->getName(), client->getName(), channel->getTopic()), server);
    serverLog("Topic ", channel->getName() + " changed by " + client->getName(), GREEN);
}

bool changeTopic(Client *client, Channel *channel) {
    if (!channel->isUser(*client)) {
        client->addCmdToSend(ERR_NOTONCHANNEL(channel->getName(), client->getName()));
        return false;
    }
    list<char> mode = channel->getMode();
    if (find(mode.begin(), mode.end(), 't') != mode.end() && !channel->isOperator(*client)) {
        client->addCmdToSend(ERR_CHANOPRIVSNEEDED(channel->getName(), client->getName()));
        return false;
    }
    return true;
}

string get_time(void) {

    struct timeval now;
	std::ostringstream oss;
	
	gettimeofday(&now, 0);
	oss << now.tv_sec;
	return oss.str();
}