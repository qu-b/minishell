/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:31:42 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/28 16:54:52 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H
#include "minishell.h"

// Define Tokens
enum e_token_type
{
	IO,
	PIPE,
	WORD,
};

// Define Token Structure
typedef struct s_token
{
	enum e_token_type type;
	char *value;
	int len;
	struct s_token *next;
} t_token;

// Lexer
int		lexer(t_token **head, char *s);

// Utils
int		is_io(char *s);
int		is_pipe(char c);
int		find_space(char *str);
int		ft_is_builtin(char *command);
void	print_tokens(t_token *head);

// Token Utils
int		str_length(char *s);
t_token *tokenize_string(char **input);
t_token *create_token(enum e_token_type type, char *value, int len);

#endif