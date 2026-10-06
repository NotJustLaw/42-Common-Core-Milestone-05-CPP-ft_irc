/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notjustlaw <notjustlaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 13:49:50 by notjustlaw        #+#    #+#             */
/*   Updated: 2026/10/06 14:01:56 by notjustlaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <string>

static bool parsePort(const std::string &str, int &port)
{
	std::stringstream ss(str); //This is way better than atoi bc it tries to interpret the string as integers.

	ss >> port;

	if (ss.fail() || !ss.eof())
		return false;
	
	if (port < 1 || port > 65535)
		return false;

	return true;
}

int main(int ac, char **av)
{
	if (ac != 3)
		return (std::cerr << "Usage: ./ircserv <port> <password>" << std::endl, 1);

	int port;

	if (!parsePort(av[1], port))
		return (std::cerr << "Error: Invalid port" << std::endl, 1);

	std::string password = av[2];
	
	if (password.empty())
		return (std::cerr << "Error: Password cannot be empty." << std::endl, 1);

	std::cout << "Starting IRC server..." << std::endl;
    std::cout << "Port: " << port << std::endl;

    return 0;
}