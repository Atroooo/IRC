#include "../header/Commands.hpp"

bool kickClient(Client Sender, Client Receiver, Channel Channel) {
    if (!Channel.isUser(Sender) || !Channel.isUser(Receiver)) {
        cout << "User not in channel" << endl;
        return false;
    }
    if (!Channel.isOperator(Sender)) {
        cout << "Operator rights required" << endl;
        return false;
    }
    Channel.removeUser(Receiver);
    return true;
}
