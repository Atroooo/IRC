#include "../header/Commands.hpp"

bool changeMode(Client Client, Channel Channel, char mode) {
    if (!Channel.isUser(Client)) {
        cout << "User not in channel" << endl;
        return false;
    }
    if (!Channel.isOperator(Client)) {
        cout << "Operator rights required" << endl;
        return false;
    }
    if (mode != 'i' || mode != 'k' || mode != 'l' || mode != 't' || mode != 'o' ) {
        cout << "Mode not supported by channel" << endl;
        return false;
    }
    Channel.setMode(mode);
    return true;
}