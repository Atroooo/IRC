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

/*------ JOIN ------*/
#define JOINCHAN(client, channel) ":" + client + " JOIN #" + channel + "\r\n"
#define INFO_JOIN(channel, topic, members) "<" + channel + "> :" + " Channel joined\nTopic " + topic + "\nMembers : " + members + "\r\n"
#define RPL_NAMREPLY(client, channel, members) ": 353 " + client + " = #" + channel + " :" + members + "\r\n" //353

/*------ INVITE ------*/
#define RPL_INVITING 341

/*------ TOPIC ------*/
#define RPL_TOPIC 332
#define RPL_NOTOPIC 331
#define RPL_TOPICWHOTIME 333


/*------ Errors ------*/
#define ERR_NEEDMOREPARAMS(cmd) ": 461 " + cmd + " :Not enough parameters\r\n" //461
#define ERR_BADCHANMASK(channel) ": 476 " + channel + " :Bad Channel Mask\r\n" //476
#define ERR_NOSUCHCHANNEL ": 403 No such channel\r\n" //403
#define ERR_BADCHANNELKEY(channel) ": 475 <" + channel + "> : Cannot join channel (+k) - bad key\r\n" //475
#define ERR_INVITEONLYCHAN(channel) ": 473 <" + channel + "> : Cannot join channel (+i) - bad key\r\n" //473
#define ERR_CHANNELISFULL(channel) ": 471 <" + channel + "> : Cannot join channel (+l) - channel full\r\n" //471
#define ERR_USERNOTINCHANNEL 441
#define ERR_NOTONCHANNEL 442
#define ERR_USERONCHANNEL 443