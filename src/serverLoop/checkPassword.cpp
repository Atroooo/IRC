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
    while (buf[i] && buf[i + 1] &&buf[i + 1] != '\n') {
        i++;
    }
    return i;
}

char * getSubStrBuffer(char *buf, char *name){
    int indexBeginning = getIndexBeginningSubStr(buf, name);
    int lenPassword = getLenSubStr(&buf[indexBeginning]);
    char *subStrName = new char[lenPassword + 1];
    strncpy(subStrName, &buf[indexBeginning],  lenPassword);
    subStrName[lenPassword] = '\0';
    return subStrName;
}

bool checkPassword(char *buf, char *serverPassword){
    char *passwordClient = getSubStrBuffer(buf, (char *)"PASS ");

    if (strcmp(passwordClient, serverPassword) != 0){
        cout << "Wrong password. " << endl;
        delete[] passwordClient;
        return (FALSE);
    }
    delete[] passwordClient;
    return true;
}

