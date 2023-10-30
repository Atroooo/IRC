#pragma once

#define SERVER_NAME "IRC"
#define TIMEOUT 100
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(param) close(param)

#define TRUE             1
#define FALSE            0

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;


/*------ Generic ------*/
#define RPL_WELCOME 001

/*-------- JOIN -------*/
#define JOINCHAN(client, channel) ":" + client + " JOIN #" + channel + "\r\n"
#define INFO_JOIN(channel, topic, members) "" + channel + " :" + " Channel joined\nTopic " + topic + "\nMembers : " + members + "\r\n"
#define RPL_NAMREPLY(client, channel, members) ": 353 " + client + " = #" + channel + " :" + members + "\r\n" //353

/*------ PRIVMSG ------*/
#define PRIVMSGCHAN(receiver, message) ": PRIVMSG #" + receiver + ":" + message + "\r\n"
#define PRIVMSGUSER(sender, receiver, message) ":" + sender + " PRIVMSG " + receiver + ":" + message + "\r\n"

/*------- INVITE ------*/
#define RPL_INVITING(client, receiver, channel) ":IRC 341 " + client + " " + receiver + " #" + channel + "\r\n" //341

/*------ TOPIC ------*/
#define RPL_TOPIC(channel, client, topic) ":IRC 332 " + client + " #" + channel + " :" + topic + "\r\n" //332
#define RPL_NOTOPIC(channel, client) ":IRC 331 " + client + " #" + channel + " :No topic is set\r\n"
#define RPL_TOPICWHOTIME(channel, client, time) ":IRC 333 " + client + " #" + channel + " " + client + " " + time + "\r\n" //333

/*------- Errors ------*/
#define ERR_NEEDMOREPARAMS(cmd) ":IRC 461 " + cmd + " :Not enough parameters\r\n" //461
#define ERR_BADCHANMASK(channel) ":IRC 476 " + channel + " #"+ channel + " :Bad Channel Mask\r\n" //476
#define ERR_NOSUCHNICK(client) ":IRC 401 " + client + " " + client  + " :No such nick\r\n" //401
#define ERR_NOSUCHCHANNEL(client, channel) ":IRC 403 " + client + " #" + channel + " :No such channel\r\n" //403
#define ERR_BADCHANNELKEY(channel) ":IRC 475 " + channel + " : Cannot join channel (+k) - bad key\r\n" //475
#define ERR_INVITEONLYCHAN(channel) ":IRC 473 " + channel + " : Cannot join channel (+i) - bad key\r\n" //473
#define ERR_CHANNELISFULL(channel) ":IRC 471 <" + channel + "> : Cannot join channel (+l) - channel full\r\n" //471
#define ERR_USERNOTINCHANNEL(channel, client, nick) ": 441 #" + channel +" " + client + " " + nick + " " + channel + " :They aren't on that channel\r\n" //441
#define ERR_NOTONCHANNEL(channel, client) ":IRC 442 #" + channel +" " + client + " " + channel + " :You're not on that channel\r\n" //442
#define ERR_USERONCHANNEL(channel, client) ":IRC 443 " + channel + " " + client + " :is already on channel\r\n" //443
#define ERR_CHANOPRIVSNEEDED(channel, client) ":IRC 482 " + client +  " #" + channel + " :You're not channel operator\r\n" //482