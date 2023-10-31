#include "../header/bot.hpp"

int main(int argc, char *argv[]){
	ServerArgument serverArgument = parsingArgument(argc, argv);
	int listening = setUpSocket(serverArgument.port);
}