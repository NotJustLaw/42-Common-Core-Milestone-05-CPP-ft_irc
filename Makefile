# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: notjustlaw <notjustlaw@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/06 13:49:28 by notjustlaw        #+#    #+#              #
#    Updated: 2026/10/06 14:00:11 by notjustlaw       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ircserv

CXX			= c++

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

HDR			= include/IRC.hpp		\
			  include/Parsing.hpp

SRC			= src/main.cpp			\
			  src/Parsing.cpp

OBJ			= $(SRC:.cpp=.o)



all: $(NAME)

$(NAME): $(HDR) $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all



.PHONY: all clean fclean re