# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhossni <yhossni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 16:20:27 by adechaji          #+#    #+#              #
#    Updated: 2025/03/09 14:49:44 by yhossni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc

R			= $(shell brew --prefix readline)

CFLAGS		:= -Wall -Wextra -Werror  -g -fsanitize=address #-I/usr/local/opt/readline

PARSSRCS	:= cleaners.c expantion.c isbuiltin.c displayread.c syncatcher.c syncatchhelpers.c tokenize_f.c \
				expantion_helpers.c rmquotes.c cmd_filler.c cmd_fillhelp.c expantion_init.c misplacing.c tokenize_help.c \
				exdoc.c signals.c exdochelp.c expa_helptw.c expa_hepdw.c

ENVSRCS	:= getenv.c env_utils.c env.c export.c export_utils.c validate_id.c export_var.c \
		   export_print.c unset.c validate_id_unset.c exit.c reset_env.c status.c

DIRSRCS := pwd.c cd.c echo.c

EXTERNSRCS := preparing_iofiles.c preparing_iofiles_utils.c prepare_args.c \
			  args_split.c prepare_args_utils.c here_doc.c multi_utils.c \
			  get_io_files.c here_doc_utils.c

EXECSRCS := improved_cmp.c exec.c builtins.c exec_utils.c externals.c multi_exec.c \
			single_process.c multi_exec_utils.c

HELPERS := ft_strlen.c ft_strdup.c ft_strncpy.c ft_lstlast.c ft_splithelpers.c \
			ft_memcpy.c ft_strncmp.c ft_strjoin.c ft_calloc.c ft_bzero.c \
			ft_substr.c arr_len.c env_size.c ft_strlcpy.c ft_strlcat.c \
			ft_strcmp.c free_tab.c ft_strtrim.c ft_atoi.c ft_strchr.c ft_split.c \
			ft_strndup.c ft_isalnum.c ft_strcpy.c delone_env.c delone_shell.c \
			clear_env.c clear_shell.c delone_token.c clear_tokens.c get_env_value.c \
			ft_realloc.c ft_itoa.c search_token.c ft_putstr_fd.c ft_old_split.c count_words.c \
			count_custom_words.c

MAIN = main.c

OBJS	:= $(addprefix objs/, $(PARSSRCS:.c=.o)) $(addprefix objs/, $(MAIN:.c=.o)) \
			$(addprefix objs/, $(HELPERS:.c=.o)) $(addprefix objs/, $(EXECSRCS:.c=.o)) \
			$(addprefix objs/, $(ENVSRCS:.c=.o)) $(addprefix objs/, $(DIRSRCS:.c=.o)) \
			$(addprefix objs/, $(EXTERNSRCS:.c=.o))

PARSSRCS := $(addprefix srcs/parsing/, $(PARSSRCS))

HELPERS := $(addprefix srcs/helpers/, $(HELPERS))

EXECSRCS := $(addprefix srcs/exec/, $(EXECSRCS)) \
			$(addprefix srcs/exec/builtins/environment/, $(ENVSRCS))

DIRSRCS := $(addprefix srcs/exec/builtins/directories/, $(DIRSRCS))

EXTERNSRCS := $(addprefix srcs/exec/externals/, $(EXTERNSRCS))

LIBS		= -lreadline -lncurses

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  $(R)/lib/libreadline.a -lncurses $(OBJS) -o $(NAME)

objs/%.o: srcs/helpers/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -I $(R)/include -c $< -o $@ -MMD

objs/%.o: srcs/parsing/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -I $(R)/include -c $< -o $@ -MMD

objs/%.o: srcs/exec/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -I $(R)/include -c $< -o $@ -MMD

objs/%.o: srcs/exec/externals/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -I $(R)/include -c $< -o $@ -MMD

objs/%.o: srcs/exec/builtins/environment/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -I $(R)/include -c $< -o $@ -MMD

objs/%.o: srcs/exec/builtins/directories/%.c
	mkdir -p objs
	$(CC) $(CFLAGS) -I $(R)/include -c $< -o $@ -MMD

objs/%.o: %.c
	mkdir -p objs
	$(CC) $(CFLAGS) -I $(R)/include -c $< -o $@ -MMD

clean:
	rm -rf objs

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(OBJS:.o=.d)
