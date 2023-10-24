#include "../../header/includes.hpp"
#include "../../header/Server.hpp"
#include "../../header/typedef.hpp"

bool checkIfIn(char *buf, char *substr){
    int i = 0;
	int len = strlen(substr);
    while (strncmp(&buf[i], substr, len) != 0 && buf[i]) {
        i++;
    }
	if (strncmp(&buf[i], substr, len) != 0){
		return false;
	}
    return true;
}

void botAction(char *buf, int clientSocket, int x){
	 if (x < 0) {
        cerr << "Error in send(). Quitting" << endl;
        //NEED EXIT
    }
	// if (buf[0] == 'J' && checkIfIn(buf, (char *)"JOIN")){
	// 	x = send(clientSocket, (char *)"Hello !", 7, 0);
	// }
	if (checkIfIn(buf, (char *)"quoi") || checkIfIn(buf, (char *)"Quoi")){
		x = send(clientSocket, "quoicoubeh", sizeof(buf), 0);
	}
	else if (checkIfIn(buf, (char *)"hein") || checkIfIn(buf, (char *)"Hein")){
		x = send(clientSocket, "apagnan", sizeof(buf), 0);
	}
	if (x < 0) {
        cerr << "Error in send(). Quitting" << endl;
        //NEED EXIT
    }
}