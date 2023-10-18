#pragma once

#include "includes.hpp"
#include "Channel.hpp"

bool createChannel(Client Client, std::string name, std::string password);

bool joinChannel(Client Client, Channel Channel, std::string password);
bool leaveChannel(Client Client, Channel Channel);

bool changeTopic(Client Client, , Channel Channel, std::string topic);
bool changeMode(Client Client, Channel Channel, char mode);

bool inviteClient(Client Sender, Client Receiver, Channel Channel);
bool kickClient(Client Sender, Client Receiver, Channel Channel);

bool sendMessage(std::string message, Channel Channel);
bool sendPrivateMessage(Client client, std::string message, Channel Channel);

bool promoteClient(Client Sender, Client Receiver, Channel Channel);
bool demoteClient(Client Sender, Client Receiver, Channel Channel);