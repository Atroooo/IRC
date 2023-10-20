#include "../header/Commands.hpp"

bool changeTopic(Client Client, Channel Channel, string topic) {
    if (!Channel.isUser(Client)) {
        cout << "User not in channel" << endl;
        return false;
    }
    if (!Channel.isOperator(Client)) {
        cout << "Operator rights required" << endl;
        return false;
    }
    Channel.setTopic(topic);
    return true;
}
