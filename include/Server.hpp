/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notjustlaw <notjustlaw@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 13:49:38 by notjustlaw        #+#    #+#             */
/*   Updated: 2026/10/06 14:10:38 by notjustlaw       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

class Server {
private:
	int _port;		// Where we want to listen.
	int _serverFd;	// The socket given by linux.

public:
	Server(int port);
	~Server();
	
	void start();
};

#endif