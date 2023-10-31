#include "../header/bot.hpp"

void connectionServer(char *password, int socketId){
	string buf;
	buf += "PASS ";
	buf += password;
	buf += "NICK BOTAndre";
	buf += "USER BOTAndre";
	buf += "\r\n";
	send(socketId, buf.c_str(), strlen(buf.c_str()), 0);
}

int main(int argc, char *argv[]){
	ServerArgument serverArgument = parsingArgument(argc, argv);
	int socketId = setUpSocket(serverArgument.port);
	connectionServer(serverArgument.password, socketId);
	return 0;
}