# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 16:20:27 by adechaji          #+#    #+#              #
#    Updated: 2025/02/17 12:58:41 by yhossni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -I/usr/local/opt/readline/include -g -fsanitize=address


PARSSRCS	:= cleaners.c crt_cmd.c parse_input.c parse_cmd.c  expantion.c \
			   redirections.c arguments.c pipes.c valid_quotes.c tokenizer.c \

ENVSRCS	:= getenv.c newenv.c findlast_env.c envadd_back.c env.c export.c

EXECSRCS := improved_cmp.c exec.c

HELPERS := ft_strlen.c ft_strdup.c ft_strncpy.c ft_lstlast.c ft_splithelpers.c \
			ft_memcpy.c ft_strncmp.c ft_strjoin.c ft_calloc.c ft_bzero.c ft_substr.c \
			arr_len.c env_size.c ft_strlcpy.c ft_strlcat.c ft_lstdelone.c

MAIN = main.c 

OBJS	:= $(addprefix objs/, $(PARSSRCS:.c=.o)) $(addprefix objs/, $(MAIN:.c=.o)) \
		   $(addprefix objs/, $(HELPERS:.c=.o)) $(addprefix objs/, $(EXECSRCS:.c=.o)) \
		   $(addprefix objs/, $(ENVSRCS:.c=.o))

PARSSRCS := $(addprefix srcs/parsing/, $(PARSSRCS))

HELPERS := $(addprefix srcs/helpers/, $(HELPERS))

EXECSRCS := $(addprefix srcs/exec/, $(EXECSRCS)) \
			$(addprefix srcs/exec/builtins/environment/, $(ENVSRCS))

LIBS		= -lreadline -lncurses

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

objs/%.o: srcs/helpers/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

objs/%.o: srcs/parsing/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

objs/%.o: srcs/exec/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

objs/%.o: srcs/exec/builtins/environment/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

objs/%.o: %.c
	mkdir -p objs
	$(CC) $(CFLAGS) -c $< -o $@ -MMD

clean:
	rm -rf objs

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(OBJS:.o=.d)