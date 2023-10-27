#include "../../header/Commands.hpp"

// join 0 to leave all channels the client is in
// if join is successful, return true and "channel: <topic>" to client + lsit of users in channel (new client included)
// Numeric Replies:
        //    ERR_NEEDMOREPARAMS            ERR_BANNEDFROMCHAN
        //    ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
        //    ERR_CHANNELISFULL               ERR_BADCHANMASK
        //    ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
        //    ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
        //    RPL_TOPIC
bool joinChannel(Client Client, Channel Channel, std::string password) {
    list<char> mode = Channel.getMode();
    if (Channel.isUser(Client)) {
        cout << "Already in channel" << endl;
        return false;
    }
    if (find(mode.begin(), mode.end(), 'k') != mode.end() && Channel.getPassword() != password) {
        cout << "Wrong password" << endl;
        return false;
    }
    if (find(mode.begin(), mode.end(), 'i') != mode.end() && !Channel.isInvited(Client)) {
        cout << "Channel is invite only" << endl;
        return false;
    }
    if (Channel.getUsers().size() >= (size_t)Channel.getMaxUsers()) {
        cout << "Channel is full" << endl;
        return false;
    }
    Channel.addUser(Client);
    return true;
}

// leave one or more channels
// can add a comment "PART #<channel>:<comment>"
//  Numeric Replies:
        //    ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
        //    ERR_NOTONCHANNEL
bool leaveChannel(Client Client, Channel Channel) {
    if (!Channel.isUser(Client)) {
        cout << "User not in channel" << endl;
        return false;
    }
    Channel.removeUser(Client);
    return true;
}

// if cmd => <topic> then display topic
// if cmd => <topic> : <comment> then change topic even if comment is empty
// Numeric Replies:
        //    ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
        //    RPL_NOTOPIC                     RPL_TOPIC
        //    ERR_CHANOPRIVSNEEDED            ERR_NOCHANMODES
bool changeTopic(Client Client, Channel Channel, std::string topic) {
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

// Numeric Replies:
        //    ERR_NEEDMOREPARAMS              ERR_KEYSET
        //    ERR_NOCHANMODES                 ERR_CHANOPRIVSNEEDED
        //    ERR_USERNOTINCHANNEL            ERR_UNKNOWNMODE
        //    RPL_CHANNELMODEIS
        //    RPL_BANLIST                     RPL_ENDOFBANLIST
        //    RPL_EXCEPTLIST                  RPL_ENDOFEXCEPTLIST
        //    RPL_INVITELIST                  RPL_ENDOFINVITELIST
        //    RPL_UNIQOPIS
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

// check valid channel
//  Numeric Replies:
        //    ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
        //    ERR_NOTONCHANNEL                ERR_USERONCHANNEL
        //    ERR_CHANOPRIVSNEEDED
        //    RPL_INVITING                    RPL_AWAY
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

// possible to kick multiple users at once + add reason if set
//  Numeric Replies:

        //    ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
        //    ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
        //    ERR_USERNOTINCHANNEL            ERR_NOTONCHANNEL
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

// Numeric Replies:

  //         ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
    //       ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
      //     ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
        //   ERR_NOSUCHNICK
          // RPL_AWAY
bool sendPrivateMessage(Client client, std::string message, Channel Channel) {
    if (message.empty()) {
        cout << "Message is empty" << endl;
        return false;
    }
    (void)Channel;
    (void)client;
    //Send message to client
    return true;
}
