#include "../header/Commands.hpp"

vector<string> getCommand(char *commandInput) {
    vector<string> command;
    
    char *cmd = strtok(commandInput, " "); 
    while (cmd != NULL) {
        command.push_back(cmd);
        cmd = strtok(NULL, " ");
    }
    return command;
}

void commandHub(char *commandInput, Client client, Server server) {
    vector<string> command = getCommand(commandInput);
    if (command[0][0] == '/') {
        if (command[0] == "/join") {
            if (command.size() < 1 || command.size() > 3) {
                cout << "Invalid command. Usage : /join [name] [pass(opt)]" << endl;
                return ;
            }
            if (!createChannel(client, server, command[1], command[2])) {
                cout << "Error creating channel" << endl;
                return ;
            }
            else {
                cout << "Channel created" << endl;
                return ;
            }
            if (!joinChannel(client, server.getChannel(command[1]), command[2])) {
                cout << "Error joining channel" << endl;
            }
            else {
                cout << "Joined channel" << endl;
                return ;
            }
        }
        return ;
    }
}

bool createChannel(Client Client, Server server, string name, string password) {
    if (server.getChannel(name) != NULL) {
        cout << "Channel already exists" << endl;
        return false;
    }
    if (name.empty()) {
        cout << "Channel name is empty" << endl;
        return false;
    }
    Channel channel(name, password);
    channel.addUser(Client);
    return true;
}

bool joinChannel(Client Client, Channel *Channel, string password) {
    if (Channel == NULL) {
        cout << "Channel does not exist" << endl;
        return false;
    }
    if (Channel->isUser(Client)) {
        cout << "Already in channel" << endl;
        return false;
    }
    list<char> mode = Channel->getMode();
    if (find(mode.begin(), mode.end(), 'k') != mode.end() && Channel->getPassword() != password) {
        cout << "Wrong password" << endl;
        return false;
    }
    if (find(mode.begin(), mode.end(), 'i') != mode.end() && !Channel->isInvited(Client)) {
        cout << "Channel is invite only" << endl;
        return false;
    }
    if (Channel->getUsers().size() >= (size_t)Channel->getMaxUsers()) {
        cout << "Channel is full" << endl;
        return false;
    }
    Channel->addUser(Client);
    return true;
}

bool leaveChannel(Client Client, Channel Channel) {
    if (!Channel.isUser(Client)) {
        cout << "User not in channel" << endl;
        return false;
    }
    Channel.removeUser(Client);
    return true;
}

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

bool promoteClient(Client Sender, Client Receiver, Channel Channel) {
    if (!Channel.isUser(Sender) || !Channel.isUser(Receiver)) {
        cout << "User not in channel" << endl;
        return false;
    }
    if (!Channel.isOperator(Sender)) {
        cout << "Operator rights required" << endl;
        return false;
    }
    Channel.addOperator(Receiver);
    return true;
}

bool sendMessage(string message, Channel Channel) {
    if (message.empty()) {
        cout << "Message is empty" << endl;
        return false;
    }
    (void)Channel;
    //Send message to all users in channel
    return true;
}

bool sendPrivateMessage(Client client, string message, Channel Channel) {
    if (message.empty()) {
        cout << "Message is empty" << endl;
        return false;
    }
    (void)Channel;
    (void)client;
    //Send message to client
    return true;
}
