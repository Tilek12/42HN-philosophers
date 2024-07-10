# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 13:26:27 by tkubanyc          #+#    #+#              #
#    Updated: 2024/07/10 17:37:41 by tkubanyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RMDIR	= rm -rf

# Source and Object files and directories
INCLUDE_DIR	= include
SRC_DIR		= src
SRC			= $(SRC_DIR)/main.c \
				$(SRC_DIR)/input_handler.c \
				$(SRC_DIR)/input_checker.c \
				$(SRC_DIR)/error_handler.c \
				$(SRC_DIR)/thread_handler.c \
				$(SRC_DIR)/mutex_handler.c \
				$(SRC_DIR)/value_handler.c \
				$(SRC_DIR)/philo_simulation.c \
				$(SRC_DIR)/philo_routines.c \
				$(SRC_DIR)/philo_action.c \
				$(SRC_DIR)/philo_utils.c \
				$(SRC_DIR)/philo_end_checker.c \
				$(SRC_DIR)/philo_cleanup.c
OBJ_DIR		= obj
OBJ			= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Header
HEADER  = $(INCLUDE_DIR)/philo.h

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)/*.o
	$(RMDIR) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
