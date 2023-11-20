#include "../../header/includes.hpp"
#include "../../header/typedef.hpp"

int getIndexBeginningSubStr(char *buf, char *name){
    int i = 0;
    while (strncmp(&buf[i], name, 5) != 0 && buf[i]) {
        i++;
    }
    return i + 5;
}

int getLenSubStr(char *buf){
    int i = 0;
    while (buf[i] && (buf[i] != '\n' && buf[i] != '\r')) {
        i++;
    }
    return i;
}

string getSubStrBuffer(char *buf, char *name){
    int indexBeginning = getIndexBeginningSubStr(buf, name);
    int indexEnd = getLenSubStr(&buf[indexBeginning]);
    string subStr = string(buf).substr(indexBeginning, indexEnd);
    return subStr;
}

bool checkPassword(char *buf, char *serverPassword){
    string passwordClient = getSubStrBuffer(buf, (char *)"PASS ");
    if (strcmp(passwordClient.c_str(), serverPassword) != 0){
        serverLog("Password ", "Wrong password", RED);
        return (FALSE);
    }
    return true;
}

bool checkIfNickNameAvailable(Server *server, string nickname) {
    if (server->getClient(nickname)){
        serverLog("Nickname ", "Nickname already taken", RED);
        return false;
    }
    return true;
}

bool checkNickClient(Client *client, string bufStr, Server *server) {
    if (client != NULL && client->getName() == "") {
        if (bufStr.find("NICK") != string::npos) {
            string nickname = getSubStrBuffer((char *)bufStr.c_str(), (char *)"NICK ");
            if (checkIfNickNameAvailable(server, nickname) == false) {
                return false;
            }
            client->setName(nickname);
            return true;
        }
        return true;
    }
    return true;
}

bool checkUserClient(Client *client, string bufStr) {
    if (client != NULL && client->getUsername() == "") {
        if (bufStr.find("USER") != string::npos) {
            string nickname = getSubStrBuffer((char *)bufStr.c_str(), (char *)"USER ");
            client->setUsername(nickname);
            return true;
        }
        return true;
    }
    return true;
}


bool checkPassClient(Client *client, string bufStr, char *serverPassword) {
    if (client != NULL && client->getPassCheck() == false) {
        if (bufStr.find("PASS") != string::npos) {
            if (checkPassword((char *)bufStr.c_str(), serverPassword) == false) {
                return false;
            }
            client->setPassCheck(true);
            return true;
        }
        return true;
    }
    return true;
}

bool checkEndOfLine(string bufStr) {
    if (bufStr.find("\n") == string::npos)
        return false;
    return true;
}

bool passAllCheck(Client *client, string bufStr, char *serverPassword, Server * server) {
    if (client == NULL)
        return (FALSE);
    if (checkPassClient(client, bufStr, serverPassword) == false) {
        return (FALSE);
    }
    if (checkNickClient(client, bufStr, server) == false) {
        return (FALSE);
    }
    if (checkUserClient(client, bufStr) == false) {
        return (FALSE);
    }
    if (strncmp(bufStr.c_str(), "QUIT", 4) == 0){
        return (FALSE);
    }
    return (TRUE);
}