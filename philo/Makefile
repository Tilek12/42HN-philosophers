# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 13:26:27 by tkubanyc          #+#    #+#              #
#    Updated: 2024/06/14 17:43:17 by tkubanyc         ###   ########.fr        #
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

# Variables
NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
RMDIR	= rm -rf

# Source and Object files
SRC		= main.c
OBJ_DIR = obj
OBJ		= $(SRC:%.c=$(OBJ_DIR)/%.o)

# Header
HEADER	= philo.h

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(L_YELLOW)Linking $@ $(RESET)"
	@{ \
	$(CC) $(OBJ) -o $(NAME) & pid=$$!; \
	spin='-\|/'; \
	i=0; \
	while kill -0 $$pid 2>/dev/null; do \
		i=$$(( (i+1) % 4 )); \
		printf "\r$(L_YELLOW)Linking $@ $(RESET)[%c]" "$${spin:$${i}:1}"; \
		sleep 0.1; \
	done; \
	wait $$pid; \
	if [ $$? -ne 0 ]; then \
		printf "\r$(YELLOW)Linking $@ $(RESET)$(RED)[failed]$(RESET)\n"; \
		exit 1; \
	else \
		printf "\r$(YELLOW)Linking $@ $(RESET)$(GREEN)[done]$(RESET)\n"; \
		printf "$(L_GREEN)"; printf "$$IMG"; printf "$(RESET)\n"; \
	fi; \
	}

$(OBJ_DIR)/%.o: %.c $(HEADER)
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
		printf "\r$(YELLOW)Compiling $< $(RESET)$(RED)[failed]$(RESET)\n"; \
		exit 1; \
	else \
		printf "\r$(YELLOW)Compiling $< $(RESET)$(GREEN)[done]$(RESET)\n"; \
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
		printf "\r$(CYAN)Cleaning object files and directories $(RESET)$(RED)[failed]$(RESET)\n"; \
		exit 1; \
	else \
		printf "\r$(CYAN)Cleaning object files and directories $(RESET)$(GREEN)[done]$(RESET)\n"; \
	fi; \
	$(RMDIR) $(OBJ_DIR); \
	}; \
	else \
		printf "\r$(L_MAGENTA)-- No object files or directories to clean --$(RESET)\n"; \
	fi;

fclean: clean
	@printf "$(L_CYAN)Cleaning executable file $(RESET)"
	@if [ -e $(NAME) ]; then \
	{ \
	$(RM) $(NAME) & pid=$$!; \
	spin='-\|/'; \
	i=0; \
	while kill -0 $$pid 2>/dev/null; do \
		i=$$(( (i+1) % 4 )); \
		printf "\r$(L_CYAN)Cleaning executable file $(RESET)[%c]" "$${spin:$${i}:1}"; \
		sleep 0.1; \
	done; \
	wait $$pid; \
	if [ $$? -ne 0 ]; then \
		printf "\r$(CYAN)Cleaning executable file $(RESET)$(RED)[failed]$(RESET)\n"; \
		exit 1; \
	else \
		printf "\r$(CYAN)Cleaning executable file $(RESET)$(GREEN)[done]$(RESET)\n"; \
	fi; \
	}; \
	else \
		printf "\r$(L_MAGENTA)------- No executable files to clean --------$(RESET)\n"; \
	fi;

re: fclean all

.PHONY: all clean fclean re
