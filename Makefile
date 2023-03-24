NAME		:= minishell
CC			:= gcc 
FLAGS		:= -Wall -Wextra -Werror -g3 -fsanitize=address
RM			:= rm -rf


SRCDIR		:= src
INCDIR		:= inc
OBJDIR		:= obj
LIBDIR		:= lib/
LIBFT		:= libft.a
SRC			:= $(wildcard $(SRCDIR)/*.c)
OBJ			:= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p '$(@D)'
			@$(CC) -c $(FLAGS) $< -o $@

all:		$(NAME)

$(NAME): 	$(OBJ)
			@$(CC) $(FLAGS) -o $@ $^ -L$(LIBDIR) -lft -lreadline

clean:
			@$(RM) $(OBJDIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
