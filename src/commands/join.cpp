#include "../header/Commands.hpp"

void joinCommand(char *commandInput, Client client, Server server) {
    string  delimiter = "#";
    vector<string> command = getCommand(commandInput, delimiter.c_str());
    if (command.size() < 1 || command.size() > 3) {
        cout << "Invalid command. Usage : /join [name] [pass(opt)]" << endl;
        return ;
    }

    if (command.size() == 2)
        command.push_back("");

    if (joinChannel(client, server.getChannel(command[1]), command[2])) 
        cout << "Joined channel" << endl;
    else if (!createChannel(client, server, command[1], command[2])) 
        cout << "Error creating channel" << endl;
    else
        cout << "Channel joined" << endl;
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