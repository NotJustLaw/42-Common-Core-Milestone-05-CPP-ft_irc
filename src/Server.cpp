/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: law <law@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 14:05:46 by notjustlaw        #+#    #+#             */
/*   Updated: 2026/11/02 12:26:18 by law              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <vector>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

#include <poll.h>

Server::Server(int port) : _port(port), _serverFd(-1), isRunning(false) {}

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

	if (bind(_serverFd, // Attach the socket to a specific local IP address and port.
			reinterpret_cast<struct sockaddr *>(&address), // Bind accepts the more generic types, thats why we cast. Bind isnt built only for IPv4.
			sizeof(address)) == -1)
		throw std::runtime_error("bind() failed");

	if (listen(_serverFd, SOMAXCONN) == -1) // SOMAXCONN is the backlog. The backlog is basically the maximum number of incoming connection requests that the OS is allowed to keep waiting while your program hasnt processed them yet.
		throw std::runtime_error("liste() failed");
	
	std::cout << "IRC server listening to port: " << _port << std::endl;
	isRunning = true;

	run();
}

void Server::run() {
	std::vector<struct pollfd> pollFds;// A growable collection of descriptors for poll() to watch.
	struct pollfd listener; // This structure tells poll() which socket to watch, what events we want, and what events actually happened.
	listener.fd = _serverFd; // Watch the listening socket. Basically asking: "Tell me when someone wants to connect."
	listener.events = POLLIN; // POLLIN asks for readable activity. On a listening socket, this means a connection is waiting to be accepted.
	listener.revents = 0; // Start with no reported events. poll() will fill this field with the events it detects on each call.

	pollFds.push_back(listener);
	
	while (isRunning) // Keep handling events until the server is told to stop by setting isRunning to false.
	{
		int ready = poll(&pollFds[0], pollFds.size(), -1); // Watch all descriptors in the vector and wait indefinitely for activity.

		if (ready == -1) // poll() returns the number of descriptors with reported events, or -1 if the call failed.
			throw std::runtime_error("poll() failed.");

		if (pollFds[0].revents & POLLIN) // revents is a set of event bits. The bitwise & checks whether POLLIN is present, even if other events were reported too.
		{
			int clientFd = accept(_serverFd, NULL, NULL); // Take a pending connection and get a new socket for that client. _serverFd keeps listening. NULL, NULL means we do not request the client's address.

			if (clientFd == -1) // No client socket was created. Skip the rest of this iteration and go back to poll().
				continue;

			if (fcntl(clientFd, F_SETFL, O_NONBLOCK) == -1) // Make this client socket non-blocking too. On Linux, accept() does not inherit O_NONBLOCK from the listening socket.
			{
				close(clientFd); // We cannot use this socket as required, so release its descriptor instead of leaving it open.
				continue; // Return to poll() and wait for another event.
			}

			std::cout << "New client conected: " << clientFd << std::endl;

			// close(clientFd); // Temporary for connection test.
			struct pollfd client;
			client.fd = clientFd;
			client.events = POLLIN; // Ask poll() to report when this client has input.
			client.revents = 0;

			pollFds.push_back(client); // Keep the connection open and include it in the next poll() call.
		}

		std::size_t i = 1; // Start at 1 because position 0 is the listening socket.

		while (i < pollFds.size())
		{
			int clientFd = pollFds[i].fd;
			short events = pollFds[i].revents;

			bool removeClient = (events & (POLLERR | POLLNVAL)) != 0;

			if (!removeClient && (events & (POLLIN | POLLHUP)))
			{
				char buffer[512];
				ssize_t received = recv(clientFd, buffer, sizeof(buffer), 0);

				if (received > 0)
				{
					std::cout << "Client " << clientFd << ": ";
					std::cout.write(buffer, received); // Print exactly the bytes received. recv() does not add a terminating '\\0'.
					std::cout.flush();
				}
				else
				{
					removeClient = true; // 0 means the peer closed its sending side. For this first test, we also close on a receive error.
				}
			}

			if (removeClient)
			{
				std::cout << "Disconnecting client: " << clientFd << std::endl;
				close(clientFd);
				pollFds.erase(pollFds.begin() + i); // Remove this entry. Later entries shift one position to the left.
			}
			else
			{
				++i; // Advance only when we did not erase, so we do not skip the client that shifted into this position.
			}
		}
	}
}
