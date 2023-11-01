#include "../header/bot.hpp"
#include <unistd.h>

void botAction(string buf, int socketId){
	if (buf.find("quoi") != string::npos || buf.find("Quoi") != string::npos){
		char *str = (char *)"PRIVMSG #BOT :str\r\n";
		usleep(1000);
		send(socketId, str, strlen(str), 0);
	}

	if (buf.find("hein") != string::npos || buf.find("Hein") != string::npos){
		char *str = (char *)"PRIVMSG #BOT :apagnan\r\n";
		usleep(1000);
		send(socketId, str, strlen(str), 0);
	}

	int randNbr = rand();
	if (randNbr % 3 == 0){
		char *str = (char *)"PRIVMSG #BOT :T'as les cramptes ?\r\n";
		usleep(1000);
		send(socketId, str, strlen(str), 0);
	}
	if (randNbr % 3 == 1){
		char *str = (char *)"PRIVMSG #BOT :menfou\r\n";
		usleep(1000);
		send(socketId, str, strlen(str), 0);
	}
	if (randNbr % 3 == 2){
		char *str = (char *)"PRIVMSG #BOT :t'es le meilleur \r\n";
		usleep(1000);
		send(socketId, str, strlen(str), 0);
	}
}