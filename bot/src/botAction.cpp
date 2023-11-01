#include "../header/bot.hpp"
#include <unistd.h>

void greetings(int socketId){
	char *str = (char *)"PRIVMSG #BOT :Bienvenue sur le channel de BOTAndre \r\n";
	usleep(1000);
	send(socketId, str, strlen(str), 0);
	return;
}

void botAction(string buf, int socketId){
	if (buf.find("JOIN") != string::npos){
		greetings(socketId);
		return;
	}
	if (buf.find("quoi") != string::npos || buf.find("Quoi") != string::npos){
		char *str = (char *)"PRIVMSG #BOT :quoicoubeh\r\n";
		usleep(1000);
		send(socketId, str, strlen(str), 0);
		return;
	}
	if (buf.find("hein") != string::npos || buf.find("Hein") != string::npos){
		char *str = (char *)"PRIVMSG #BOT :apagnan\r\n";
		usleep(1000);
		send(socketId, str, strlen(str), 0);
		return;
	}
	int randNbr = rand();
	if (randNbr % 3 == 0){
		char *str = (char *)"PRIVMSG #BOT :T'as les cramptes ?\r\n";
		usleep(1000);
		send(socketId, str, strlen(str), 0);
	}
	else if (randNbr % 3 == 1){
		char *str = (char *)"PRIVMSG #BOT :menfou\r\n";
		usleep(1000);
		send(socketId, str, strlen(str), 0);
	}
	else if (randNbr % 3 == 2){
		char *str = (char *)"PRIVMSG #BOT :t'es le meilleur \r\n";
		usleep(1000);
		send(socketId, str, strlen(str), 0);
	}
}