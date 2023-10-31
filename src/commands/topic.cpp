#include "../../header/Commands.hpp"

void topicCommand(string commandInput, Client client, Server *server) {

    vector<string> command = initCommand(commandInput);
    if (command.size() < 2) {
        sendInfoClient(client, ERR_NEEDMOREPARAMS(string(""),string("TOPIC")));
        return ;
    }
    if (channelMask(command) == false) {
        sendInfoClient(client, ERR_BADCHANMASK(command[1].substr(1)));
        return ;
    }
    Channel *channel = server->getChannel(command[1].substr(1));
    if (channel == NULL) {
        sendInfoClient(client, ERR_NOSUCHCHANNEL(client.getName(), command[1].substr(1)));
        return ;
    }
    if (commandInput.find(':') == string::npos) {
        if (channel->getTopic() == "No topic") {
            sendInfoClient(client, RPL_NOTOPIC(channel->getName(), client.getName()));
            return ;
        }
        sendInfoClient(client, RPL_TOPIC(channel->getName(), client.getName(), channel->getTopic()));
        return ;
    }
    if (!changeTopic(client, channel)) {
        return ;
    }
    channel->setTopic(commandInput.substr(commandInput.find(':') + 1));
    sendInfoChannel(*channel, RPL_TOPICWHOTIME(channel->getName(), client.getName(), get_time()));
    sendInfoChannel(*channel, RPL_TOPIC(channel->getName(), client.getName(), channel->getTopic()));
}

bool changeTopic(Client client, Channel *channel) {
    if (!channel->isUser(client)) {
        sendInfoClient(client, ERR_NOTONCHANNEL(channel->getName(), client.getName()));
        return false;
    }
    if (!channel->isOperator(client)) {
        sendInfoClient(client, ERR_CHANOPRIVSNEEDED(channel->getName(), client.getName()));
        return false;
    }
    return true;
}

#include <ctime>
#include <sstream>
#include <sys/time.h>
string get_time(void) {

    struct timeval now;
	std::ostringstream oss;
	
	gettimeofday(&now, 0);
	oss << now.tv_sec;
	return oss.str();
}
