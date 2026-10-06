/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notjustlaw <notjustlaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 14:05:46 by notjustlaw        #+#    #+#             */
/*   Updated: 2026/10/06 17:44:41 by notjustlaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <iostream>
#include <stdexcept>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

Server::Server(int port) : _port(port), _serverFd(-1) {}

Server::~Server()
{
	if (_serverFd != -1)
		close(_serverFd);
}

void Server::start()
{
	// On IPv4, SOCK_STREAM with protocol 0 resolves to TCP. AF_INET selects the IPv4 address family.
	_serverFd = socket(AF_INET, SOCK_STREAM, 0); // Ask linux to give his process a network socket. AF_INET = IPv4 && SOCK_STREAM = TCP. Basically asking: "Give me an IPv4 TCP socket."
	if (_serverFd == -1)
		throw std::runtime_error("socket() failed");
	
	int enable = 1; // This is to enable the SO_REUSEADDR to allow this local address/port to be reused under normal TCP restart conditions.
	
    if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1) // Without SO_REUSEADDR, you can sometimes get: "Address already in use".
		throw std::runtime_error("setsockopt() failed");

	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("fcntl() failed");
	
	struct sockaddr_in address; // sockkaddr_in is the IPv4-specific socket-address type.

	std::memset(&address, 0, sizeof(address)); //Memory initialization to 0.

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY); // host to network long since we are looking to store a 32-bit int.
	address.sin_port = htons(_port); // host to network short since we are looking to store a 16-bit int.

    if (bind(_serverFd,										//	Attach the socket to a specific local IP address and port.
            reinterpret_cast<struct sockaddr *>(&address), // Bind accepts the more generic types, thats why we cast. Bind isnt built only for IPv4.
            sizeof(address)) == -1)
        throw std::runtime_error("bind() failed");

	if (listen(_serverFd, SOMAXCONN) == -1) // SOMAXCONN is the backlog. The backlog is basically the maximum number of incoming connection requests that the OS is allowed to keep waiting while your program hasnt processed them yet.
		throw std::runtime_error("liste() failed");
	
	std::cout << "IRC server listening to port: " << _port << std::endl;
}