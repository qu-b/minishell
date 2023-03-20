NAME		= minishell
CC			:= gcc 
FLAGS		:= -I$(INCDIR) -Wall -Wextra -Werror
RM			:= rm -rf


SRCDIR		:= src
INCDIR		:= inc
OBJDIR		:= obj
SRC			:= $(wildcard $(SRCDIR)/*.c)
OBJ			:= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p '$(@D)'
			@$(CC) -c $(FLAGS) $< -o $@

all:		$(NAME)

$(NAME): 	$(OBJ)
			@$(CC) $^ $(FLAGS) -lreadline -o $(NAME)

clean:
			@$(RM) $(OBJDIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
