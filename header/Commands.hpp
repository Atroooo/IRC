#pragma once

#include "includes.hpp"
#include "Channel.hpp"

void commandHub(char *commandInput, Client client, Server server);

bool createChannel(Client client, Server server, string name, string password);

bool joinChannel(Client Client, Channel *Channel, string password);
bool leaveChannel(Client Client, Channel Channel);

bool changeTopic(Client Client, Channel Channel, string topic);
bool changeMode(Client Client, Channel Channel, char mode);

bool inviteClient(Client Sender, Client Receiver, Channel Channel);
bool kickClient(Client Sender, Client Receiver, Channel Channel);

bool sendMessage(string message, Channel Channel);
bool sendPrivateMessage(Client client, string message, Channel Channel);

bool promoteClient(Client Sender, Client Receiver, Channel Channel);
bool demoteClient(Client Sender, Client Receiver, Channel Channel);