# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adechaji <adechaji@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 16:20:27 by adechaji          #+#    #+#              #
#    Updated: 2025/02/14 22:12:57 by adechaji         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I/usr/local/opt/readline/include -g #-fsanitize=address
SRCS		= src/cleaners.c src/crt_cmd.c src/ft_lstadd_back.c src/ft_lstlast.c \
				src/ft_split.c src/ft_splithelpers.c src/helpers.c src/parse_input.c \
				src/ft_memcpy.c src/ft_strncmp.c src/parse_cmd.c src/ft_strdup.c src/ft_strlen.c \
				src/redirections.c src/arguments.c src/pipes.c src/valid_quotes.c src/tokenizer.c src/ft_strncpy.c \
				src/main.c
				#src/displayread.c
OBJS		= $(SRCS:.c=.o)
LIBS		= -lreadline -lncurses

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
