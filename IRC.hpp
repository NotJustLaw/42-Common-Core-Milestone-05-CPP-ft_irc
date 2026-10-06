/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-alme <pde-alme@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 20:33:40 by pde-alme          #+#    #+#             */
/*   Updated: 2026/10/06 20:50:33 by pde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>

# define PWD_MAX_CHARS 512

/* Text colouring macros. */
# define DEF "\033[0m"
# define BLA "\033[90m"
# define RED "\033[91m"
# define GRE "\033[92m"
# define YEL "\033[93m"
# define BLU "\033[94m"
# define MAG "\033[95m"
# define CYA "\033[96m"
# define WHI "\033[97m"

/* Structure for storing server credentials after parsing.
 */
typedef struct  s_cred
{
    unsigned short  port;
    char            *pass;
    std::string     pass_str;
}   t_cred;

#endif
