# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/02 15:16:38 by supersko          #+#    #+#              #
#    Updated: 2022/06/18 17:44:20 by supersko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = error_msg.c ft_atoi.c ft_atoi_err.c ft_bzero.c ft_calloc.c \
	ft_get_next_wd.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
	ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strlen_char.c ft_strmapi.c ft_strncmp.c	\
	ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
	ft_toupper.c ft_wd_count.c ft_free_split.c

OBJS := ${SRCS:c=o}

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

CC = gcc

all: ${NAME}

${NAME}: ${OBJS}
	ar rcs $@ $?

%.o: %.c
	${CC} ${CFLAGS} -c $<

.PHONY: ctags
ctags:
	ctags *

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

test: ctags
	${CC} ${SRCS}
	./a.out
	rm -f a.out

debug: ctags
	${CC} -g ${SRCS}
	lldb a.out
	rm -f a.out

.PHONY: all clean fclean re
# If, for example, the file clean happened to be created running make clean would yield the confusing message:
# $ make clean
# make: `clean' is up to date.Makefile
