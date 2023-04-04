NAME		:= minishell
CC			:= gcc 
FLAGS		:= #-Wall -Wextra -Werror -g3 -fsanitize=address
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
			@$(CC) $(FLAGS) -o $@ $^ -I/opt/local/include -L/opt/local/lib -lreadline -L$(LIBDIR) -lft -I$(INCDIR) 
#Somehow MacOs Ventura readline doesnt have rl_replace_line, so i linked against one I installed with MacPorts
#Remove -I/opt/local/include and -L/opt/local/lib if it works for you :)
run:		all
			@./minishell

clean:
			@$(RM) $(OBJDIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
