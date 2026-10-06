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

#include "../include/Parsing.hpp"

int	main(int argc, char **argv)
{
	t_cred	*credentials = Parsing::parse(argc, argv);
	if (!credentials)
		return (1);
	
	// Start server loop;
	// Print server "ready" message;

	delete (credentials);
    return (0);
}