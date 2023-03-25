NAME		:= minishell
CC			:= gcc 
FLAGS		:= -Wall -Wextra -Werror -g3 -fsanitize=address
RM			:= rm -rf


SRCDIR		:= src_builtins src_minishell src_parser
INCDIR		:= inc
OBJDIR		:= obj
LIBDIR		:= lib/
LIBFT		:= libft.a
SRC			:= $(shell find $(SRCDIR) -name '*.c')
OBJ			:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))


$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p '$(@D)'
			@$(CC) -c $(FLAGS) $< -o $@

all:		$(NAME)

$(NAME): 	$(OBJ)
			@$(CC) $(FLAGS) -o $@ $^ -L$(LIBDIR) -lft -lreadline -I$(INCDIR)

run:		all
			@./minishell

clean:
			@$(RM) $(OBJDIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
