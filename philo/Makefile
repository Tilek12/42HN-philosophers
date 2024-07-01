# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 13:26:27 by tkubanyc          #+#    #+#              #
#    Updated: 2024/06/29 21:24:12 by tkubanyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ASCII Art
define IMG

          888      d8b 888                                     888
          888      Y8P 888                                     888
          888          888                                     888
 88888b.  88888b.  888 888  .d88b.  .d8888b   .d88b.  88888b.  88888b.   .d88b.  888d888 .d8888b
 888 "88b 888 "88b 888 888 d88""88b 88K      d88""88b 888 "88b 888 "88b d8P  Y8b 888P"   88K
 888  888 888  888 888 888 888  888 "Y8888b. 888  888 888  888 888  888 88888888 888     "Y8888b.
 888 d88P 888  888 888 888 Y88..88P      X88 Y88..88P 888 d88P 888  888 Y8b.     888          X88
 88888P"  888  888 888 888  "Y88P"   88888P'  "Y88P"  88888P"  888  888  "Y8888  888      88888P'
 888                                                  888
 888                                                  888
 888                                                  888

endef

export IMG

# Define ANSI color escape codes
RED			= \033[0;31m
L_RED		= \033[1;31m
GREEN		= \033[0;32m
L_GREEN		= \033[1;32m
YELLOW		= \033[0;33m
L_YELLOW 	= \033[1;33m
BLUE		= \033[0;34m
L_BLUE		= \033[1;34m
MAGENTA		= \033[0;35m
L_MAGENTA	= \033[1;35m
CYAN		= \033[0;36m
L_CYAN		= \033[1;36m
WHITE		= \033[1;37m
RESET		= \033[0m

#-fsanitize=address -fno-omit-frame-pointer

# Variables
NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
#LDFLAGS = -fsanitize=address
# -fsanitize=thread
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
				$(SRC_DIR)/philo_run.c \
				$(SRC_DIR)/philo_action.c \
				$(SRC_DIR)/philo_utils.c
OBJ_DIR		= obj
OBJ			= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Header
HEADER  = $(INCLUDE_DIR)/philo.h

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(L_YELLOW)Linking $@ $(RESET)"
	@{ \
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) & pid=$$!; \
	spin='-\|/'; \
	i=0; \
	while kill -0 $$pid 2>/dev/null; do \
		i=$$(( (i+1) % 4 )); \
		printf "\r$(L_YELLOW)Linking $@ $(RESET)[%c]" "$${spin:$${i}:1}"; \
		sleep 0.1; \
	done; \
	wait $$pid; \
	if [ $$? -ne 0 ]; then \
		printf "\r$(YELLOW)Linking $@  $(RESET)❌$(RED)[failed]$(RESET)\n"; \
		exit 1; \
	else \
		printf "\r$(YELLOW)Linking $@  $(RESET)✅$(GREEN)[done]$(RESET)\n"; \
		printf "$(L_GREEN)"; printf "$$IMG"; printf "$(RESET)\n"; \
	fi; \
	}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@printf "$(L_YELLOW)Compiling $< $(RESET)"
	@{ \
	$(CC) $(CFLAGS) -c $< -o $@ & pid=$$!; \
	spin='-\|/'; \
	i=0; \
	while kill -0 $$pid 2>/dev/null; do \
		i=$$(( (i+1) % 4 )); \
		printf "\r$(L_YELLOW)Compiling $< $(RESET)[%c]" "$${spin:$${i}:1}"; \
		sleep 0.1; \
	done; \
	wait $$pid; \
	if [ $$? -ne 0 ]; then \
		printf "\r$(YELLOW)Compiling $<  $(RESET)❌$(RED)[failed]$(RESET)\n"; \
		exit 1; \
	else \
		printf "\r$(YELLOW)Compiling $<  $(RESET)✅$(GREEN)[done]$(RESET)\n"; \
	fi; \
	}

clean:
	@printf "$(L_CYAN)Cleaning object files and directories $(RESET)"
	@if [ -d $(OBJ_DIR) ]; then \
	{ \
	$(RM) $(OBJ_DIR)/*.o & pid=$$!; \
	spin='-\|/'; \
	i=0; \
	while kill -0 $$pid 2>/dev/null; do \
		i=$$(( (i+1) % 4 )); \
		printf "\r$(L_CYAN)Cleaning object files and directories $(RESET)[%c]" "$${spin:$${i}:1}"; \
		sleep 0.1; \
	done; \
	wait $$pid; \
	if [ $$? -ne 0 ]; then \
		printf "\r$(CYAN)Cleaning object files and directories  $(RESET)❌$(RED)[failed]$(RESET)\n"; \
		exit 1; \
	else \
		printf "\r$(CYAN)Cleaning object files and directories  $(RESET)✅$(GREEN)[done]$(RESET)\n"; \
	fi; \
	$(RMDIR) $(OBJ_DIR); \
	}; \
	else \
		printf "\r$(L_MAGENTA)-- No object files or directories to clean --$(RESET)\n"; \
	fi;

fclean: clean
	@printf "$(L_CYAN)Cleaning executable files $(RESET)"
	@if [ -e $(NAME) ]; then \
	{ \
	$(RM) $(NAME) & pid=$$!; \
	spin='-\|/'; \
	i=0; \
	while kill -0 $$pid 2>/dev/null; do \
		i=$$(( (i+1) % 4 )); \
		printf "\r$(L_CYAN)Cleaning executable files $(RESET)[%c]" "$${spin:$${i}:1}"; \
		sleep 0.1; \
	done; \
	wait $$pid; \
	if [ $$? -ne 0 ]; then \
		printf "\r$(CYAN)Cleaning executable files  $(RESET)❌$(RED)[failed]$(RESET)\n"; \
		exit 1; \
	else \
		printf "\r$(CYAN)Cleaning executable files  $(RESET)✅$(GREEN)[done]$(RESET)\n"; \
	fi; \
	}; \
	else \
		printf "\r$(L_MAGENTA)------- No executable files to clean --------$(RESET)\n"; \
	fi;

re: fclean all

.PHONY: all clean fclean re
