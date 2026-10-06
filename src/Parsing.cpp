/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-alme <pde-alme@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 20:21:41 by pde-alme          #+#    #+#             */
/*   Updated: 2026/10/06 20:21:42 by pde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Parsing.hpp"

const char  *Parsing::HelpCommandException::what(void) const throw()
{
    return (GRE "USAGE" DEF ": ./ircserv [port] [password]");
}

const char  *Parsing::InvalidArgsException::what(void) const throw()
{
    return (RED "ERROR" DEF ": Invalid amount of arguments!");
}

const char  *Parsing::InvalidPortException::what(void) const throw()
{
    return (RED "ERROR" DEF ": Invalid port number!");
}

const char  *Parsing::InvalidPassException::what(void) const throw()
{
    return (RED "ERROR" DEF ": Invalid password characters!");
}

Parsing::Parsing() {}

Parsing::~Parsing() {}

/* Prints a small server initialization message.
 */
void    Parsing::printStartupMsg(t_cred *credentials)
{
    std::cout << "Initializing" CYA " IRC " DEF "server in port " MAG << credentials->port << DEF "..." << std::endl;
}

/* Counts the amount of arguments passed as parameter to the program. If an
 * invalid amount was passed, print the specified output and throw an exception.
 */
void    Parsing::countArgs(int argc, char** argv) throw(HelpCommandException, InvalidArgsException)
{
    if (argc != 3)
    {
        if (argc == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help"))
            throw HelpCommandException();
        throw InvalidArgsException();
    }
}

/* Checks whether the port number, specified as parameter, has a valid range.
 * If not, or if non-digit characters are found, throw an excpetion.
 *
 * Port 0 connection failure should be handled only when attempting to create the
 * connection, even though port 0 is already reserved, but so can other ports be.
 * 
 * NOTE: Length 18 is one number below the "long" type total decimal houses (to
 * prevent overflowing back to a valid number, if too large).
 */
void    Parsing::checkPort(char **argv) throw(InvalidPortException)
{
    std::string port(argv[1]);

    if (port.length() < 1 || port.length() > 18)
        throw InvalidPortException();
    for (std::string::iterator iter(port.begin()); iter != port.end(); iter++)
        if (!std::isdigit(*iter))
            throw InvalidPortException();
    if (std::strtol(argv[1], NULL, 10) > 65535)
        throw InvalidPortException();
}

/* Checks whether the password, specified as parameter, has a valid length (and
 * under the RFC-1459 IRC standard maximum password length). If not, or if any
 * whitespace character is found, throw an exception.
 */
void    Parsing::checkPass(char **argv) throw(InvalidPassException)
{
    std::string pass(argv[2]);

    if (pass.length() < 1 || pass.length() > PWD_MAX_CHARS)
        throw InvalidPassException();
    for (std::string::iterator iter(pass.begin()); iter != pass.end(); iter++)
        if (std::iswspace(*iter))
            throw InvalidPassException();
}

/* Allocates a new "t_cred" structure and appends all parameter values to their
 * specified structure field. It either returns the memory allocated structure
 * or throws an exception if there is no memory left.
 */
t_cred  *Parsing::buildCred(char **argv) throw(std::bad_alloc)
{
    t_cred  *credentials;
    
    credentials = new t_cred;
    credentials->port = std::strtol(argv[1], NULL, 10);
    credentials->pass = argv[2];
    credentials->pass_str = std::string(argv[2]);
    printStartupMsg(credentials);
    return (credentials);
}

/* Main function for the "Parsing" class. This function will call all of the
 * class's private functions to determine whether the program was initialized
 * with correct arguments.
 * 
 * If any issues are found, the specific issuing function's exception will be
 * catched, have its message printed and return "NULL" back to the caller.
 */
t_cred  *Parsing::parse(int argc, char **argv)
{
    try
    {
        countArgs(argc, argv);
        checkPort(argv);
        checkPass(argv);
        return (buildCred(argv));
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (NULL);
    }
}

/* Prints the values of the structure passed as parameter.
 * For debugging purposes only.
 */
void    Parsing::debugStructure(t_cred *credentials)
{
    std::cout << RED "---> t_struct DEBUG: <---" DEF << std::endl;
    std::cout << MAG "PORT" DEF ":\t\t" YEL << credentials->port << DEF << std::endl;
    std::cout << MAG "PASS" DEF ":\t\t" YEL << credentials->pass << DEF << std::endl;
    std::cout << MAG "PASS (string)" DEF ":\t" YEL << credentials->pass_str << DEF << std::endl;
}