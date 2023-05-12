NAME		:= minishell
CC			:= gcc 
FLAGS		:= -Wall -Wextra -Werror -g3 #-fsanitize=address
RM			:= rm -rf


SRCDIR		:= src_builtins src_minishell src_parser src_heredoc
INCDIR		:= inc
OBJDIR		:= obj
LIBDIR		:= lib/
LIBFT		:= libft.a
SRC			:= $(shell find $(SRCDIR) -name '*.c')
OBJ			:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

define HEADER
            _       _     _          _ _ 
           (_)     (_)   | |        | | |
  _ __ ___  _ _ __  _ ___| |__   ___| | |
 | '_ ` _ \| | '_ \| / __| '_ \ / _ \ | |
 | | | | | | | | | | \__ \ | | |  __/ | |
 |_| |_| |_|_|_| |_|_|___/_| |_|\___|_|_|
                                         
                                         
endef
export HEADER

$(OBJDIR)/%.o: $(SRCDIR)/%.c
			@mkdir -p '$(@D)'
			@$(CC) -c $(FLAGS) $< -o $@

all:		$(NAME)

$(NAME): 	$(OBJ)
			@$(CC) $(FLAGS) -o $@ $^ -I/usr/local/Cellar/readline/8.2.1/include -L/usr/local/Cellar/readline/8.2.1/lib/ -I/opt/local/include -L/opt/local/lib -lreadline -L$(LIBDIR) -lft -I$(INCDIR) 
#			@$(CC) $(FLAGS) -o $@ $^ -I/Users/$(USER)/.brew/Cellar/readline/8.2.1/include -L/Users/$(USER)/.brew/Cellar/readline/8.2.1/lib -lreadline -L$(LIBDIR) -lft -I$(INCDIR)

#On school computers run :
# curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
# brew install readline
#Use the second compile command

run:		all
			@echo "$$HEADER"
			@./minishell

clean:
			@$(RM) $(OBJDIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
