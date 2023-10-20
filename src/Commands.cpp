#include "../header/Commands.hpp"

bool createChannel(Client Client, std::string name, std::string password) {
    //Gerer cas ou le channel existe deja mais a voir ou est ce qu on stock les channels ? class server ??
    if (name.empty()) {
        cout << "Channel name is empty" << endl;
        return false;
    }
    Channel channel(name, password);
    channel.addUser(Client, 1);
    return true;
}

bool joinChannel(Client Client, Channel Channel, std::string password) {
    //Gerer invite only mode apres => ajouter un is invited par Client dans une map, et idem pour admin?
    list<char> mode = Channel.getMode();
    // if (Channel.isUser(Client))
    //     throw alreadyInChannel();
    if (find(mode.begin(), mode.end(), 'k') != mode.end() && Channel.getPassword() != password)
        throw wrongPassword();
    if (find(mode.begin(), mode.end(), 'i') != mode.end())
        throw opRightRequired();
    if (Channel.getUsers().size() >= (size_t)Channel.getMaxUsers())
        throw channelFull();
    Channel.addUser(Client, 1);
    return true;
}

bool leaveChannel(Client Client, Channel Channel) {
    // if (!Channel.isUser(Client))
    //     throw notInChannel();
    // Channel.removeUser(Client);
    (void) Client, (void) Channel;
    return true;
}

bool changeTopic(Client Client, Channel Channel, std::string topic) {
    // if (!Channel.isUser(Client))
    //     throw notInChannel();
    // if (!Channel.isOperator(Client))
    //     throw opRightRequired();
    (void) Client;
    Channel.setTopic(topic);
    return true;
}

bool changeMode(Client Client, Channel Channel, char mode) {
    // if (!Channel.isUser(Client))
    //     throw notInChannel();
    // if (!Channel.isOperator(Client))
    //     throw opRightRequired();
    (void) Client;
    Channel.setMode(mode);
    return true;
}

bool inviteClient(Client Sender, Client Receiver, Channel Channel) {
    // if (!Channel.isUser(Sender) || !Channel.isUser(Receiver))
    //     throw notInChannel();
    // if (!Channel.isOperator(Sender))
    //     throw opRightRequired();
    (void) Sender, (void) Receiver, (void) Channel;
    if (Channel.getUsers().size() >= (size_t)Channel.getMaxUsers())
        throw channelFull();
    Channel.addUser(Receiver, 0);
    return true;
}

bool kickClient(Client Sender, Client Receiver, Channel Channel) {
    // if (!Channel.isUser(Sender) || !Channel.isUser(Receiver))
    //     throw notInChannel();
    // if (!Channel.isOperator(Sender))
    //     throw opRightRequired();
    // Channel.removeUser(Receiver);
    (void) Sender, (void) Receiver, (void) Channel;
    return true;
}

bool sendMessage(std::string message, Channel Channel) {
    if (message.empty())
        throw std::exception();
    (void)Channel;
    //Send message to all users in channel
    return true;
}

bool sendPrivateMessage(Client client, std::string message, Channel Channel) {
    if (message.empty())
        throw std::exception();
    (void)Channel;
    (void)client;
    //Send message to client
    return true;
}

bool promoteClient(Client Sender, Client Receiver, Channel Channel) {
    // if (!Channel.isUser(Sender) || !Channel.isUser(Receiver))
    //     throw notInChannel();
    // if (!Channel.isOperator(Sender))
    //     throw opRightRequired();
    // Channel.addOperator(Receiver); TODO
    (void) Sender, (void) Receiver, (void) Channel;
    return true;
}
