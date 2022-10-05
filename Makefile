# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swalter <swalter@student.42mulhouse.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 15:16:38 by supersko          #+#    #+#              #
#    Updated: 2022/10/05 12:38:02 by supersko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = *.c

OBJS := ${SRCS:c=o}

#MAIN = main.c

NAME = minishell
DEBUG_NAME = a.out
HEADERS = include
LIBFT_DIR = libft/
LIBFT_AR = libft.a
LIBS = $(LIBFT_DIR)$(LIBFT_AR)

INCLUDES = -I./usr/include -I./$(HEADERS) $(LIBS) -I./$(LIBFTprintf_DIR) -I./$(LIBFT_DIR) -I/$(HOME)/.brew/opt/readline/include
CFLAGS = -Wall -Wextra -Werror -L/$(HOME)/.brew/opt/readline/lib -lreadline -g3 -fsanitize=address 

CC = gcc

all: ${NAME}

${NAME}: make_libft
	$(CC) $(CFLAGS) $(SRCS) $(LIBS)  $(INCLUDES) -o $(NAME)
#	$(CC) $(CFLAGS) $(SRCS) $(LIBS) $(MAIN) $(INCLUDES) -o $(NAME)

%.o: %.c
	${CC} ${CFLAGS} $(INCLUDES) -c $<

make_libft:
	make -C libft

.PHONY: ctags
ctags:
	ctags *

clean:
	rm -f $(OBJS)
	rm -f $(DEBUG_NAME)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

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
