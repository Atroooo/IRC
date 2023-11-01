#pragma once

#include "includes.hpp"

void commandHub(string commandInput, Client *client, Server *server);
vector<string> initCommand(string commandInput);
bool channelMask (vector<string> command, Client * client);

void joinCommand(string command, Client *client, Server *server);
bool createChannel(Client *client, Server *server, string name, string password);
int  joinChannel(Client *client, Channel *channel, string password, Server *server);

void leaveCommand(string command, Client *client, Server *server);
bool leaveChannel(Client *client, Channel *channel, string message, Server *server);
void leaveAllChannels(Client *client, Server *server);
vector<string> split(string str, char delimiter, vector<string> &result);

void topicCommand(string command, Client *client, Server *server);
bool changeTopic(Client *client, Channel *channel);
string get_time(void);

void modeCommand(string command, Client *client, Server *server);
bool changeMode(Client *client, Channel *channel);
bool promoteClient(Client *sender, Client *receiver, Channel *channel, Server * server);
bool demoteClient(Client *sender, Client *receiver, Channel *channel, Server * server);
string toString(int number);

void inviteCommand(string command, Client *client, Server *server);
bool inviteClient(Client *sender, Client receiver, Channel *channel);

void kickCommand(string command, Client *client, Server *server);
bool kickClient(Client *sender, Client receiver, Channel *channel, Server * server);

void sendMessageCommand(string CommandInput, Client * client, Server *server);
bool sendMessage(Channel *channel, string message, Server *server, Client *sender);
bool sendPrivateMessage(Client *sender, Client *receiver, string message);