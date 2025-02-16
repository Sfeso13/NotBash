# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 16:20:27 by adechaji          #+#    #+#              #
#    Updated: 2025/02/16 09:44:27 by yhossni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -I/usr/local/opt/readline/include -g #-fsanitize=address
PARSSRCS		= cleaners.c crt_cmd.c ft_lstadd_back.c ft_lstlast.c \
				ft_split.c ft_splithelpers.c helpers.c parse_input.c \
				ft_memcpy.c ft_strncmp.c parse_cmd.c ft_strdup.c ft_strlen.c \
				redirections.c arguments.c pipes.c valid_quotes.c tokenizer.c ft_strncpy.c \
				main.c 
				#displayread.c
OBJS		:= $(addprefix objs/, $(PARSSRCS:.c=.o))
PARSSRCS := $(addprefix parsing/src/, $(PARSSRCS))
LIBS		= -lreadline -lncurses

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

objs/%.o: parsing/src/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

clean:
	rm -rf objs

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(OBJS:.o=.d)