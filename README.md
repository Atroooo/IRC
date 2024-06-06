<p align="center">
  <img src="https://raw.githubusercontent.com/PKief/vscode-material-icon-theme/ec559a9f6bfd399b82bb44393651661b08aaf7ba/icons/folder-markdown-open.svg" width="100" alt="project-logo">
</p>
<p align="center">
    <h1 align="center">IRC</h1>
</p>
<p align="center">
    <em>Empower your chat with infinite possibilities!</em>
</p>
<p align="center">
	<img src="https://img.shields.io/github/license/Atroooo/IRC?style=default&logo=opensourceinitiative&logoColor=white&color=0080ff" alt="license">
	<img src="https://img.shields.io/github/last-commit/Atroooo/IRC?style=default&logo=git&logoColor=white&color=0080ff" alt="last-commit">
	<img src="https://img.shields.io/github/languages/top/Atroooo/IRC?style=default&color=0080ff" alt="repo-top-language">
	<img src="https://img.shields.io/github/languages/count/Atroooo/IRC?style=default&color=0080ff" alt="repo-language-count">
<p>
<p align="center">
	<!-- default option, no dependency badges. -->
</p>

<br><!-- TABLE OF CONTENTS -->

<details>
  <summary>Table of Contents</summary><br>

-   [ Overview](#-overview)
-   [ Repository Structure](#-repository-structure)
-   [ Modules](#-modules)
-   [ Getting Started](#-getting-started)
    -   [ Installation](#-installation)
    -   [ Usage](#-usage)
    -   [ Tests](#-tests)

</details>
<hr>

## Overview

The IRC project, IRC Server Implementation, offers a robust platform for hosting Internet Relay Chat servers. It includes functionalities such as client actions, message sending, and server setup, enabling efficient communication within IRC channels. Key modules like server management, channel operations, and client interactions enhance user experience. The project's value lies in providing a reliable and feature-rich environment for real-time text communication among users within defined server networks.

---

## Repository Structure

```sh
└── IRC/
    ├── Makefile
    ├── bot
    │   ├── Makefile
    │   ├── header
    │   └── src
    ├── header
    │   ├── Channel.hpp
    │   ├── Client.hpp
    │   ├── Commands.hpp
    │   ├── Server.hpp
    │   ├── includes.hpp
    │   ├── serverUtils.hpp
    │   └── typedef.hpp
    └── src
        ├── class
        ├── commands
        ├── main.cpp
        ├── parsingArgument
        ├── serverLoop
        └── setUpSocket
```

---

## Modules

<details closed><summary>.</summary>

| File                                                            | Summary                                                                                                                                                                                                                                  |
| --------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [Makefile](https://github.com/Atroooo/IRC/blob/master/Makefile) | Compiles an IRC server using C++, handling IRC functionalities. Organizes code into separate modules and compiles them into an executable binary for the server. Key features include client actions, message sending, and server setup. |

</details>

<details closed><summary>bot</summary>

| File                                                                | Summary                                                                                                                                                                               |
| ------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [Makefile](https://github.com/Atroooo/IRC/blob/master/bot/Makefile) | Compiles and creates a bot executable. Defines dependencies, compiles source files, and generates the final binary. Implements clean, fclean, and re targets for project maintenance. |

</details>

<details closed><summary>bot.header</summary>

| File                                                                     | Summary                                                                                                                    |
| ------------------------------------------------------------------------ | -------------------------------------------------------------------------------------------------------------------------- |
| [bot.hpp](https://github.com/Atroooo/IRC/blob/master/bot/header/bot.hpp) | Parses command-line arguments and sets up a socket for IRC bot operation. Executes bot actions based on incoming messages. |

</details>

<details closed><summary>bot.src</summary>

| File                                                                                          | Summary                                                                                                                                                                                                                                                                         |
| --------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [parsingArgument.cpp](https://github.com/Atroooo/IRC/blob/master/bot/src/parsingArgument.cpp) | Validates and extracts server port and password from command line arguments, ensuring the port is within acceptable range. Facilitates error handling for incorrect argument count and non-numeric port inputs in the IRC bot setup.                                            |
| [setUpSocket.cpp](https://github.com/Atroooo/IRC/blob/master/bot/src/setUpSocket.cpp)         | Enables socket setup and binding for IRC bot functionality, facilitating connection to a designated server and port. Incorporated in the bot module, this code ensures socket creation and communication establishment, pivotal for network interactions within the IRC system. |
| [botAction.cpp](https://github.com/Atroooo/IRC/blob/master/bot/src/botAction.cpp)             | Implements bot actions for IRC chat, including welcoming messages and responses based on specific keywords. Engages with the IRC server through the provided socket ID, enhancing user interaction within the BOTAndre channel.                                                 |
| [bot.cpp](https://github.com/Atroooo/IRC/blob/master/bot/src/bot.cpp)                         | Establishes IRC bot connection, joins channel, and retrieves server messages. Implements key functions for server interaction. Key features include establishing connection, handling messages, and shutting down gracefully.                                                   |

</details>

<details closed><summary>header</summary>

| File                                                                                 | Summary                                                                                                                                                                                                                                                                          |
| ------------------------------------------------------------------------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [Server.hpp](https://github.com/Atroooo/IRC/blob/master/header/Server.hpp)           | Defines Server class managing clients and channels, provides methods to access and manipulate client and channel lists, add/remove clients and channels, and check client existence. Includes functions for sending info/messages to clients and waiting for client connections. |
| [Channel.hpp](https://github.com/Atroooo/IRC/blob/master/header/Channel.hpp)         | Defines Channel class with properties and methods to manage channel settings, users, and operations within the IRC system. Maintains user access control, mode settings, and client management for effective communication and collaboration.                                    |
| [Commands.hpp](https://github.com/Atroooo/IRC/blob/master/header/Commands.hpp)       | Hub, join, leave, topic, mode, invite, kick, send messages. Facilitates channel and client actions within the IRC server setup.                                                                                                                                                  |
| [includes.hpp](https://github.com/Atroooo/IRC/blob/master/header/includes.hpp)       | Orchestrates key libraries, classes, and utilities for IRC server-client interactions. Integrates server setup, client management, command handling, and channel operations. Facilitates robust, efficient communication within the IRC system.                                  |
| [serverUtils.hpp](https://github.com/Atroooo/IRC/blob/master/header/serverUtils.hpp) | Parse args, set up socket, manage clients, send data, remove channels, log actions. Performs critical server-side operations for networking and client interactions in the IRC repository.                                                                                       |
| [Client.hpp](https://github.com/Atroooo/IRC/blob/master/header/Client.hpp)           | Manages client data and actions including setting name, storing commands, and handling user registration status within the IRC system.                                                                                                                                           |
| [typedef.hpp](https://github.com/Atroooo/IRC/blob/master/header/typedef.hpp)         | Defines constants, message formats, and error codes for an IRC client in the parent repository. Enhances readability and maintainability by centralizing textual representations and protocol-specific details.                                                                  |

</details>

<details closed><summary>src</summary>

| File                                                                | Summary                                                                                                                                                                                                  |
| ------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [main.cpp](https://github.com/Atroooo/IRC/blob/master/src/main.cpp) | Initializes server socket for communication, sets up file descriptors, and starts the server loop with specified arguments. Supports efficient server operation within the IRC repositorys architecture. |

</details>

<details closed><summary>src.parsingArgument</summary>

| File                                                                                                      | Summary                                                                                                                                                      |
| --------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| [parsingArgument.cpp](https://github.com/Atroooo/IRC/blob/master/src/parsingArgument/parsingArgument.cpp) | Validates and extracts server startup arguments to ensure correct port format and range. Returns validated server arguments for initializing the IRC server. |

</details>

<details closed><summary>src.setUpSocket</summary>

| File                                                                                          | Summary                                                                                                                                                                                                                                    |
| --------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| [setUpSocket.cpp](https://github.com/Atroooo/IRC/blob/master/src/setUpSocket/setUpSocket.cpp) | Enables setting up and listening on a socket for incoming connections on a specified port. Handles socket creation, configuration, binding, and listening processes to establish network communication within the IRC server architecture. |

</details>

<details closed><summary>src.serverLoop</summary>

| File                                                                                           | Summary                                                                                                                                                                                                                                            |
| ---------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [serverLoop.cpp](https://github.com/Atroooo/IRC/blob/master/src/serverLoop/serverLoop.cpp)     | Manages connections, sends messages, handles channels, and logs events. Maintains active clients and dynamically updates channels. Signals server closure when needed, connecting various components seamlessly.                                   |
| [checkClient.cpp](https://github.com/Atroooo/IRC/blob/master/src/serverLoop/checkClient.cpp)   | Implements client connection checks in server loop for password, nickname, username validation. Evaluates buffer for data integrity and client status. Integrates client input processing and server password validation for secure communication. |
| [clientAction.cpp](https://github.com/Atroooo/IRC/blob/master/src/serverLoop/clientAction.cpp) | Implements client actions handling for the server, ensuring proper command parsing and execution. It checks for end-of-line, processes client input, and handles multiple client connections efficiently.                                          |

</details>

<details closed><summary>src.class</summary>

| File                                                                            | Summary                                                                                                                                                                                                                                                                    |
| ------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [Client.cpp](https://github.com/Atroooo/IRC/blob/master/src/class/Client.cpp)   | Defines a client class with basic attributes and methods for managing client connections in an IRC system. Enables setting and retrieving client information such as name, file descriptor, username, and commands to send.                                                |
| [Channel.cpp](https://github.com/Atroooo/IRC/blob/master/src/class/Channel.cpp) | Manages channel properties, users, and permissions within the IRC system. Implements methods to handle channel operations like adding/removing users, setting modes, and checking user statuses. Enhances communication and moderation functionalities in the IRC network. |
| [Server.cpp](https://github.com/Atroooo/IRC/blob/master/src/class/Server.cpp)   | Provides Server class methods to manage clients and channels within the IRC system. Allows adding, retrieving, and removing clients and channels. Verifies client existence. Works with the parent repositorys architecture to handle server functionality.                |

</details>

<details closed><summary>src.commands</summary>

| File                                                                                       | Summary                                                                                                                                                                                                                                              |
| ------------------------------------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| [sendMessage.cpp](https://github.com/Atroooo/IRC/blob/master/src/commands/sendMessage.cpp) | Implements functions to handle sending messages to channels or users based on input commands. Validates input, determines message recipients, and sends messages accordingly within the IRC server architecture.                                     |
| [kick.cpp](https://github.com/Atroooo/IRC/blob/master/src/commands/kick.cpp)               | Implements a robust kick command handling logic for IRC channels in the repository. Validates client and channel existence, authorization, and executes proper kick actions with informative channel notifications and logging.                      |
| [topic.cpp](https://github.com/Atroooo/IRC/blob/master/src/commands/topic.cpp)             | Implements topic command logic for IRC channels, validating and updating topics as users interact. Handles topic changes, permissions, and time stamps.                                                                                              |
| [leave.cpp](https://github.com/Atroooo/IRC/blob/master/src/commands/leave.cpp)             | Implements leave functionality for IRC channels, validating inputs and handling user exits gracefully. Supports leaving specific channels and all channels in the server.                                                                            |
| [Commands.cpp](https://github.com/Atroooo/IRC/blob/master/src/commands/Commands.cpp)       | Executes various IRC commands for registered clients, ensuring required parameters are set. Converts commands to uppercase for case-insensitivity. Validates channel masks and handles message routing and user interactions effectively.            |
| [invite.cpp](https://github.com/Atroooo/IRC/blob/master/src/commands/invite.cpp)           | Implements invite functionality for IRC server. Validates client existence and parameters, invites user to channel, handles various error scenarios, and logs invite actions. Helps manage the invitation process efficiently within the IRC system. |
| [join.cpp](https://github.com/Atroooo/IRC/blob/master/src/commands/join.cpp)               | Validates and parses JOIN commands, creates and joins channels, and enforces channel access rules. Handles channel membership, passwords, and server interactions effectively for IRC bot functionality.                                             |
| [mode.cpp](https://github.com/Atroooo/IRC/blob/master/src/commands/mode.cpp)               | Implements mode command logic for IRC channels. Enforces user permissions, manages channel modes like passwords and user limits, and handles operator promotions and demotions. Enhances channel interaction and security within the IRC system.     |

</details>

---

## Getting Started

**System Requirements:**

-   **CPP**: `version x.y.z`

### Installation

<h4>From <code>source</code></h4>

> 1. Clone the IRC repository:
>
> ```console
> $ git clone https://github.com/Atroooo/IRC
> ```
>
> 2. Change to the project directory:
>
> ```console
> $ cd IRC
> ```
>
> 3. Install the dependencies:
>
> ```console
> $ make
> ```

### Usage

<h4>From <code>source</code></h4>

> Run IRC using the command below:
>
> ```console
> $ ./IRC your_port server_password
> ```
