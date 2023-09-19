# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/08 13:22:20 by ccarrace          #+#    #+#              #
#    Updated: 2023/09/19 19:27:54 by ccarrace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# gcc -Wall -Wextra -Werror -g -fsanitize=address -I inc/ main.c ft_utils.c -o philo

# --- Variables ----------------------------------------------------------------
CC			=		gcc
NAME		=		philo

# --- Compiler flags -----------------------------------------------------------

FLAGS		=		-MMD -Wall -Wextra -Werror #-fsanitize=thread -g

# --- Directories --------------------------------------------------------------

HEADER_DIR	=		inc/

# --- Includes -----------------------------------------------------------------

INCLUDES	=		-I $(HEADER_DIR)

# --- Files --------------------------------------------------------------------

SRC_FILES	=		main.c \
					initializing.c \
					starting.c \
					philo_routine.c \
					health_checkup.c \
					printing.c \
					ft_utils.c

# --- Macros -------------------------------------------------------------------

OBJ_FILES = $(SRC_FILES:.c=.o)
DEP_FILES = $(SRC_FILES:.c=.d)

# --- Compilation rules --------------------------------------------------------

all:		$(NAME)

$(NAME): 	$(OBJ_FILES)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJ_FILES) -o $@

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEP_FILES)

# --- Cleaning rules --------------------------------------------------------- #

clean:
			rm -f $(OBJ_FILES) $(DEP_FILES)

fclean: 	clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re