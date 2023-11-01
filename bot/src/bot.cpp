#include "../header/bot.hpp"
#include <unistd.h>

void connectionServer(char *password, int socketId){
	string buf;
	buf += "PASS ";
	buf += password;
	buf += " \n";
	buf += " NICK BOTAndre\n";
	buf += " USER BOTAndre\n";
	buf += "\r\n";
	send(socketId, buf.c_str(), strlen(buf.c_str()), 0);
}

void joinChannel(int socketId){
	usleep(1000);
	string buf = "JOIN #BOT\r\n";
	send(socketId, buf.c_str(), strlen(buf.c_str()), 0);
}

bool	stopSignal = false;

static void	shutdown(int)
{
	stopSignal = true;
}

void getServerMessage(int socketId){
	char buffer[1024];
	while (stopSignal == false) {
		int bytesRead = recv(socketId, buffer, sizeof(buffer) - 1, 0);
		if (bytesRead < 0) {
			perror("Error receiving data");
			break;
		}
		if (bytesRead == 0) {
			std::cout << "Connection closed by server." << std::endl;
			break;
		}
		buffer[bytesRead] = '\0';
		botAction(buffer, socketId);
	}
	usleep(1000);
	send(socketId, "QUIT\r\n", 7, 0);
}

int main(int argc, char *argv[]){
	ServerArgument serverArgument = parsingArgument(argc, argv);
	int socketId = setUpSocket(serverArgument.port);
	connectionServer(serverArgument.password, socketId);
	joinChannel(socketId);
	getServerMessage(socketId);
	return 0;
}