/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:47:12 by lcompieg          #+#    #+#             */
/*   Updated: 2023/10/16 15:18:10 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

int main(int argc, char **argv)
{
    int bufsize = 1024;
    char buffer[bufsize];

    if (argc != 3) {
        std::cout << "Usage: ./irc [port] [password]" << std::endl;
        return (1);
    }
    SOCKET sock;
if (sock_err == SOCKET_ERROR) {
        std::cout << "Error: " << sock_err << std::endl;
        return (1);
    }sock = socket(AF_INET, SOCK_STREAM, 0);
    
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);   
    sin.sin_family = AF_INET;
    sin.sin_port = htons(atoi(argv[1]));
    
    int sock_err = bind(sock, (SOCKADDR*)&sin, sizeof(sin));
    if (sock_err == SOCKET_ERROR) {
        std::cout << "Error: " << sock_err << std::endl;
        return (1);
    }
    std::cout << "Binded" << std::endl;
    int sock_err1 = listen(sock, 5);
    if (sock_err1 == SOCKET_ERROR) {
        std::cout << "Error: " << sock_err1 << std::endl;
        return (1);
    }
    std::cout << "Listening" << std::endl;
    // SOCKADDR_IN csin;
    // SOCKET csock;
    // socklen_t taille = sizeof(csin);
    std::cout << "Waiting for connection" << std::endl;
    socklen_t taille = sizeof(sin);
    int server = accept(sock, (struct sockaddr *)&sin, &taille);
    if (server < 0) 
        std::cout << "=> Error on accepting..." << std::endl;
    while (server > 0) {
        recv(server, buffer, bufsize, 0);
        std::cout << buffer << " ";
        pause();
    }
    // std::cout << "Accepted" << std::endl;
    // std::cout << "Connected " << inet_ntoa(csin.sin_addr) << std::endl;
    // closesocket(csock);
    // closesocket(sock);
    // std::cout << "Closed" << std::endl;
    return (0); 
}