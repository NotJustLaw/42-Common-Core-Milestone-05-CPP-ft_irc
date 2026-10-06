/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-alme <pde-alme@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 20:05:27 by pde-alme          #+#    #+#             */
/*   Updated: 2026/10/06 20:05:30 by pde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
# define PARSING_HPP

# include <cstdlib>
# include <exception>
# include "IRC.hpp"

/* Static "Parsing" class that will house every parsing-related function.
 */
class Parsing
{
    class HelpCommandException : public std::exception { public: const char *what(void) const throw(); };
    class InvalidArgsException : public std::exception { public: const char *what(void) const throw(); };
    class InvalidPortException : public std::exception { public: const char *what(void) const throw(); };
    class InvalidPassException : public std::exception { public: const char *what(void) const throw(); };

    private:
        Parsing();
        ~Parsing();
        static void     printStartupMsg(t_cred *credentials);
        static void     countArgs(int argc, char **argv) throw(HelpCommandException, InvalidArgsException);
        static void     checkPort(char **argv) throw(InvalidPortException);
        static void     checkPass(char **argv) throw(InvalidPassException);
        static t_cred   *buildCred(char **argv) throw(std::bad_alloc);

    public:
        static t_cred   *parse(int argc, char **argv);
        static void     debugStructure(t_cred *credentials);
};

#endif