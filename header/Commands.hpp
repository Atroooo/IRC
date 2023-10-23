#pragma once

#include "includes.hpp"

void commandHub(char *commandInput, Client client, Server server);

void joinCommand(vector<string> command, Client client, Server server);
bool createChannel(Client client, Server server, string name, string password);
bool joinChannel(Client Client, Channel *Channel, string password);

void leaveCommand(vector<string> command, Client client, Server server);
bool leaveChannel(Client client, Channel *channel, string message);

void topicCommand(vector<string> command, Client client, Server server);
bool changeTopic(Client client, Channel *channel, string topic);

void modeCommand(vector<string> command, Client client, Server server);
bool changeMode(Client client, Channel *channel, char mode);

void inviteCommand(vector<string> command, Client client, Server server);
bool inviteClient(Client sender, Client receiver, Channel *channel);

void kickCommand(vector<string> command, Client client, Server server);
bool kickClient(Client sender, Client receiver, Channel *channel);

void changeRightsCommand(vector<string> command, Client sender, Channel *channel);
bool promoteClient(Client sender, Client receiver, Channel *channel);
bool demoteClient(Client sender, Client receiver, Channel *channel);

bool sendMessage(Client client, Channel *channel, string message);
bool sendPrivateMessage(Client client, string message);