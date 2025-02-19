# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroseiro <jroseiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/16 03:55:00 by jroseiro          #+#    #+#              #
#    Updated: 2025/02/19 18:48:33 by jroseiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = philo

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
FSANITIZE = -fsanitize=thread

# Source files
SRCS = 	main.c \
		inits.c \
		utils.c \
		actions.c \
		monitor.c \
		threads.c \
		action_utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header file
HEADER = sources.h

# Default target
all: $(NAME)

# Compile program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# FSanitize compilation
f: CFLAGS += $(FSANITIZE)
f: re

# Compile source files to object files
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean object files and program
fclean: clean
	rm -f $(NAME)

# Clean and recompile
re: fclean all

# Declare phony targets
.PHONY: all clean fclean re f
