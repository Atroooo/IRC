#pragma once

#include "includes.hpp"

class unknownClient : std::exception {
    public:
        const char *what() const throw() { return "Unknown  or missing client"; };
};

class unknownChannel : std::exception {
    public:
        const char *what() const throw() { return "Unknown  or missing channel"; };
};

class opRightRequired : std::exception {
    public:
        const char *what() const throw() { return "Operator rights required"; };
};

class wrongPassword : std::exception {
    public:
        const char *what() const throw() { return "Wrong password"; };
};

class alreadyInChannel : std::exception {
    public:
        const char *what() const throw() { return "Client already in channel"; };
};

class notInChannel : std::exception {
    public:
        const char *what() const throw() { return "Client not in channel"; };
};

class channelFull : std::exception {
    public:
        const char *what() const throw() { return "Channel is full"; };
};