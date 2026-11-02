/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: law <law@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 13:49:38 by notjustlaw        #+#    #+#             */
/*   Updated: 2026/11/02 11:09:03 by law              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

class Server {
private:
	int _port;		// Where we want to listen.
	int _serverFd;	// The socket given by linux.
	bool isRunning;

public:
	Server(int port);
	~Server();
	
	void start();
	void run();
};

#endif