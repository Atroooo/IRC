/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcompieg <lcompieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:47:12 by lcompieg          #+#    #+#             */
/*   Updated: 2023/10/16 12:48:57 by lcompieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int argc, char **argv)
{
    (void) argv;
    if (argc != 3) {
        std::cout << "Usage: ./irc [port] [password]" << std::endl;
        return (1);
    }
    return (0);
}