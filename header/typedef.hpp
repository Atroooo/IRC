#pragma once

#define SERVER_NAME "IRC"
#define TIMEOUT 100
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(param) close(param)

#define TRUE             1
#define FALSE            0

#define SERVER_NAME "IRC"

#define RPL_NOTOPIC 331
#define RPL_TOPIC 332
#define RPL_TOPICWHOTIME 333
#define RPL_INVITING 341
#define ERR_NOSUCHCHANNEL 403
#define ERR_USERNOTINCHANNEL 441
#define ERR_NOTONCHANNEL 442
#define ERR_USERONCHANNEL 443
#define ERR_NEEDMOREPARAMS 461
#define ERR_BADCHANMASK 476
#define ERR_CHANOPRIVSNEEDED 482

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;


/*------ Generic ------*/
#define RPL_WELCOME "001"

/*------ JOIN ------*/
#define RPL_NAMREPLY "353"