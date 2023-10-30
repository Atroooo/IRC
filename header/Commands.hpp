#pragma once

#include "includes.hpp"

void commandHub(string commandInput, Client *client, Server *server);
vector<string> initCommand(string commandInput);
bool channelMask (vector<string> command);

void joinCommand(string command, Client *client, Server *server);
bool createChannel(Client client, Server *server, string name, string password);
int  joinChannel(Client client, Channel *channel, string password);

void leaveCommand(string command, Client client, Server *server);
bool leaveChannel(Client client, Channel *channel, string message);
vector<string> split(string str, char delimiter, vector<string> &result);

void topicCommand(string command, Client client, Server *server);
bool changeTopic(Client client, Channel *channel);
string get_time(void);

void modeCommand(string command, Client client, Server *server);
bool changeMode(Client client, Channel *channel, char mode);
bool promoteClient(Client sender, Client receiver, Channel *channel);
bool demoteClient(Client sender, Client receiver, Channel *channel);

void inviteCommand(string command, Client client, Server *server);
bool inviteClient(Client sender, Client receiver, Channel *channel);

void kickCommand(string command, Client client, Server *server);
bool kickClient(Client sender, Client receiver, Channel *channel);

void sendMessageCommand(string CommandInput, Client client, Server *server);
bool sendMessage(Client client, Channel *channel, string message);
bool sendPrivateMessage(Client sender, Client *receiver, string message);

void checkRetSend(int ret);
void sendInfoClient(Client client, string msg);
void sendInfoChannel(Channel channel, string msg);

//DELETE
void printVector(vector<string> vec);