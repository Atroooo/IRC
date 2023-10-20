#include "../header/Commands.hpp"

bool leaveChannel(Client Client, Channel Channel) {
    if (!Channel.isUser(Client)) {
        cout << "User not in channel" << endl;
        return false;
    }
    Channel.removeUser(Client);
    return true;
}