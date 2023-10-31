#pragma once

/*Libraries*/
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <csignal>
#include <stdlib.h>
#include <poll.h>
#include <fcntl.h>
#include <ctime>
#include <sys/time.h>
#include <algorithm>
#include <map>
#include <list>
#include <vector>

using namespace std;

/*Classes*/
#include "Server.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "Commands.hpp"
#include "typedef.hpp"
#include "serverUtils.hpp"
