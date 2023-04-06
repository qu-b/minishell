/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:31:42 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/06 06:57:30 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

// Define Token Type
enum e_token_type
{
	IO,
	PIPE,
	WORD,
};

// Define Token Structure
typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	int					len;
	struct s_token		*next;
}	t_token;

typedef struct s_data
{
	t_token	*tokens;
	char	**env;
	int		pid; // needed for signal handling
}	t_data;


int		parser(char *input);

// Lexer
int		lexer(t_token **head, char *s);
void	process_tokens(t_token *tokens);

// Utils
int		is_io(char *s);
int		is_pipe(char c);
int		find_space(char *str);
int		ft_is_builtin(char *cmd);
void	print_tokens(t_token *head);

// Token Utils
int		str_length(char *s);
t_token	*tokenize_string(char **input);
t_token	*create_token(enum e_token_type type, char *value, int len);

#endif
