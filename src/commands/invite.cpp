#include "../header/Commands.hpp"

bool inviteClient(Client Sender, Client Receiver, Channel Channel) {
    
    if (!Channel.isUser(Sender)) {
        cout << "User not in channel" << endl;
        return false;
    }
    if (Channel.isUser(Receiver)) {
        cout << "User already in channel" << endl;
        return false;
    }
    list<char> mode = Channel.getMode();
    if (find(mode.begin(), mode.end(), 'i') != mode.end() && !Channel.isOperator(Sender)) {
        cout << "Operator rights required" << endl;
        return false;
    }
    if (Channel.getUsers().size() >= (size_t)Channel.getMaxUsers()) {
        cout << "Channel is full" << endl;
        return false;
    }
    Channel.addUser(Receiver);
    return true;
}