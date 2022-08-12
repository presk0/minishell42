# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: supersko <supersko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 15:16:38 by supersko          #+#    #+#              #
#    Updated: 2022/08/12 12:48:31 by supersko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c prompting.c utils.c init.c debug.c split.c matrix.c strings.c\
	var_conv.c parser.c exec_cmd.c get_filename.c pipe.c bultins2.c env.c verif_bultin.c\
	command.c bin.c

OBJS := ${SRCS:c=o}

#MAIN = main.c

NAME = minishell
DEBUG_NAME = a.out
HEADERS = include
LIBFT_DIR = libft/
LIBFTPRINTF_DIR = libftprintf/
LIBFT_AR = libft.a
LIBFTPRINTF_AR = libftprintf.a
LIBS = $(LIBFTPRINTF_DIR)$(LIBFTPRINTF_AR) $(LIBFT_DIR)$(LIBFT_AR)

INCLUDES = -I./$(HEADERS) $(LIBS) -I./$(LIBFTPRINTF_DIR) -I./$(LIBFT_DIR)
CFLAGS = -Wall -Wextra -Werror -lreadline -g3 -fsanitize=address 

CC = gcc

all: ${NAME}

${NAME}: make_libftprintf make_libft
	$(CC) $(CFLAGS) $(SRCS) $(LIBS)  $(INCLUDES) -o $(NAME)
#	$(CC) $(CFLAGS) $(SRCS) $(LIBS) $(MAIN) $(INCLUDES) -o $(NAME)

%.o: %.c
	${CC} ${CFLAGS} $(INCLUDES) -c $<

make_libft:
	make -C libft

make_libftprintf:
	make -C libftprintf

.PHONY: ctags
ctags:
	ctags *

clean:
	rm -f $(OBJS)
	rm -f $(DEBUG_NAME)
	make clean -C libft
	make clean -C libftprintf

fclean: clean
	rm -f $(NAME)
	make fclean -C libft
	make fclean -C libftprintf

re: fclean all

test: ctags
	${CC} $(CFLAGS) $(INCLUDES) ${SRCS} -o $(NAME)
	./$(NAME)
	rm  -f a.out

debugfile: ctags
	$(CC) $(CFLAGS) -g $(SRCS)  $(INCLUDES) -o $(DEBUG_NAME) -fsanitize=address
#	$(CC) $(CFLAGS) -g $(SRCS) $(MAIN) $(INCLUDES) -o $(DEBUG_NAME) -fsanitize=address

debug: debugfile
	lldb $(DEBUG_NAME)
	rm -f $(DEBUG_NAME)

.PHONY: all clean fclean re
