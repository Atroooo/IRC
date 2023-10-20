#include "../../header/includes.hpp"
#include "../../header/typedef.hpp"

int getIndexBeginningPassword(char *buf){
    int i = 0;
    while (strncmp(&buf[i], "PASS ", 5) != 0 && buf[i]) {
        i++;
    }
    return i + 5;
}

int getLenPassword(char *buf){
    int i = 0;
    while (buf[i] && buf[i + 1] &&buf[i + 1] != '\n') {
        i++;
    }
    return i;
}

char *getPassword(char *buf){
    int indexBeginning = getIndexBeginningPassword(buf);
    int lenPassword = getLenPassword(&buf[indexBeginning]);
    char *passwordClient = new char[lenPassword + 1];
    strncpy(passwordClient, &buf[indexBeginning],  lenPassword);
    passwordClient[lenPassword] = '\0';
    return passwordClient;
}

bool checkPassword(char *buf, char *serverPassword){
    char *passwordClient = getPassword(buf);
    if (strcmp(passwordClient, serverPassword) != 0){
        cout << "Wrong password. " << endl;
        delete[] passwordClient;
        return (FALSE);
    }
    delete[] passwordClient;
    return true;
}

