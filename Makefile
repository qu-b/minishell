NAME		:= minishell
CC			:= gcc 
FLAGS		:= -Wall -Wextra -Werror -g3 -fsanitize=address
RM			:= rm -rf


SRCDIR		:= src_builtins src_minishell src_parser src_heredoc
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
			@$(CC) $(FLAGS) -o $@ $^ -I/usr/local/Cellar/readline/8.2.1/include -L/usr/local/Cellar/readline/8.2.1/lib/ -I/opt/local/include -L/opt/local/lib -lreadline -L$(LIBDIR) -lft -I$(INCDIR) 
#			@$(CC) $(FLAGS) -o $@ $^ -I/Users/$(USER)/.brew/Cellar/readline/8.2.1/include -L/Users/$(USER)/.brew/Cellar/readline/8.2.1/lib -lreadline -L$(LIBDIR) -lft -I$(INCDIR)

#Somehow MacOs Ventura readline doesnt have rl_replace_line, so i linked against one I installed with MacPorts
#Remove -I/opt/local/include and -L/opt/local/lib if it works for you :)
#I had the same problem and installed it using Homebrew.
#Replace -I/usr/local/Cellar/readline/8.2.1/include -L/usr/local/Cellar/readline/8.2.1/lib/
#as needed. 
#👍
#On school computers run :
# curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
# brew install readline
#Use the second compile command

run:		all
			@./minishell

clean:
			@$(RM) $(OBJDIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
