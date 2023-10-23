#pragma once

#include "includes.hpp"

void commandHub(string commandInput, Client client, Server *server);
vector<string> initCommand(string commandInput);
bool channelMask (vector<string> command);

void joinCommand(string command, Client client, Server *server);
bool createChannel(Client client, Server *server, string name, string password);
bool joinChannel(Client Client, Channel *Channel, string password);

void leaveCommand(string command, Client client, Server *server);
bool leaveChannel(Client client, Channel *channel, string message);

void topicCommand(string command, Client client, Server *server);
bool changeTopic(Client client, Channel *channel, string topic);

void modeCommand(string command, Client client, Server *server);
bool changeMode(Client client, Channel *channel, char mode);

void inviteCommand(string command, Client client, Server *server);
bool inviteClient(Client sender, Client receiver, Channel *channel);

void kickCommand(string command, Client client, Server *server);
bool kickClient(Client sender, Client receiver, Channel *channel);
void sendKickMessage(Client client, Client *receiver, Channel *channel, vector<string> command);

void changeRightsCommand(string command, Client sender, Server *server);
bool promoteClient(Client sender, Client receiver, Channel *channel);
bool demoteClient(Client sender, Client receiver, Channel *channel);

bool sendMessage(Client client, Channel *channel, string message);
bool sendPrivateMessage(Client client, string message);