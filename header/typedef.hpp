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
#define RPL_WELCOME "001"

/*------ JOIN ------*/
#define RPL_NAMREPLY "353"