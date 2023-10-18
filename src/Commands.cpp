#include "../header/Commands.hpp"

// bool createChannel(Client Client, std::string name, std::string password) {
//     //Gerer cas ou le channel existe deja mais a voir ou est ce qu on stock les channels ? class server ??
//     if (name.empty()) {
//         cout << "Channel name is empty" << endl;
//         return false;
//     }
//     Channel channel(name, password);
//     channel.addUser(Client);
//     channel.addOperator(Client);
// }

// bool joinChannel(Client Client, Channel Channel, std::string password) {
//     //Gerer invite only mode apres => ajouter un is invited par Client dans une map, et idem pour admin?
//     if (Channel.isUser(Client))
//         throw alreadyInChannel();
//     // if (find(Channel.getMode(), 'k') && Channel.getPassword() != password)
//     //     throw wrongPassword();
//     // if (Channel.getMode().find('i'))
//     //     throw opRightRequired();
//     if (Channel.getUsers().size() >= (size_t)Channel.getMaxUsers())
//         throw channelFull();
//     Channel.addUser(Client);
// }

// bool leaveChannel(Client Client, Channel Channel) {
//     if (!Channel.isUser(Client))
//         throw notInChannel();
//     Channel.removeUser(Client);
// }

// bool changeTopic(Client Client, Channel Channel, std::string topic) {
//     if (!Channel.isUser(Client))
//         throw notInChannel();
//     if (!Channel.isOperator(Client))
//         throw opRightRequired();
//     Channel.setTopic(topic);
// }

// bool changeMode(Client Client, Channel Channel, char mode) {
//     if (!Channel.isUser(Client))
//         throw notInChannel();
//     if (!Channel.isOperator(Client))
//         throw opRightRequired();
//     Channel.setMode(mode);
// }

// bool inviteClient(Client Sender, Client Receiver, Channel Channel) {
//     if (!Channel.isUser(Sender) || !Channel.isUser(Receiver))
//         throw notInChannel();
//     if (!Channel.isOperator(Sender))
//         throw opRightRequired();
//     if (Channel.getUsers().size() >= (size_t)Channel.getMaxUsers())
//         throw channelFull();
//     Channel.addUser(Receiver);
// }

// bool kickClient(Client Sender, Client Receiver, Channel Channel) {
//     if (!Channel.isUser(Sender) || !Channel.isUser(Receiver))
//         throw notInChannel();
//     if (!Channel.isOperator(Sender))
//         throw opRightRequired();
//     Channel.removeUser(Receiver);
// }

// bool sendMessage(std::string message, Channel Channel) {
//     if (message.empty())
//         throw std::exception();
//     //Send message to all users in channel
// }

// bool sendPrivateMessage(Client client, std::string message, Channel Channel) {
//     if (message.empty())
//         throw std::exception();
//     //Send message to client
// }

// bool promoteClient(Client Sender, Client Receiver, Channel Channel) {
//     if (!Channel.isUser(Sender) || !Channel.isUser(Receiver))
//         throw notInChannel();
//     if (!Channel.isOperator(Sender))
//         throw opRightRequired();
//     Channel.addOperator(Receiver);
// }