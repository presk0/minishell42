
NAME = minishell


SRCS = main.c prompting.c utils.c init.c debug.c split.c matrix.c strings.c\
	var_conv.c exec_cmd.c get_filename.c pipe2.c bultins2.c env.c verif_bultin.c\
	command.c bin.c export.c cde_bash.c pipe.c

OBJS = $(SRCS:.c=.o)

CC = gcc 

CFLAGS += -Wall -Werror -Wextra -g3 -fsanitize=address
#CFLAGS += -g3 -fsanitize=address
FLAGREADLINE = -L/Users/swalter/.brew/opt/readline/lib -lreadline
CPPFLAGS= -I/Users/swalter/.brew/opt/readline/include
RM = rm -rf

LIBFT = libft.a
LIBFTDIR = libft/
LIBFTLINK = -L $(LIBFTDIR) -lft


all:		$(NAME)

$(NAME):	complib  $(OBJS) 
	$(CC) $(LIBFTLINK) $(FLAGREADLINE) $(CFLAGS) -o $@ $(OBJS) 

complib:
	$(MAKE) -C libft/

%.o:		%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS)  -o $@ $<


clean:
	$(MAKE) -C $(LIBFTDIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(OBJS)
	$(RM) $(NAME)

re:		fclean all

leaks:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

git:
	make fclean
	git add .
	git commit -m "make done"
	git push

norme:
	norminette ./srcs/* ./libft/*

.PHONY:		all clean fclean re leaks git norme
