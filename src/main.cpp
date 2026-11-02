/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: law <law@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 13:49:50 by notjustlaw        #+#    #+#             */
/*   Updated: 2026/11/02 11:36:23 by law              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Parsing.hpp"
#include "../include/Server.hpp"

int main(int argc, char **argv)
{
    t_cred *credentials = Parsing::parse(argc, argv);
    if (!credentials)
        return 1;

    try
    {
        Server server(credentials->port);
        server.start();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        delete credentials;
        return 1;
    }

    delete credentials;
    return 0;
}