/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:31:42 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/24 15:35:05 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "../inc/minishell.h"

// Define Tokens
enum e_token_type {
	CMD,
	ARG,
	PATH,
	STR,
	IO,
	PIPE,
	VAR,
	EXIT
};

// Define Token Structure
typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	int					len;
}	t_token;

// Utils
int	is_space(char c);
int	is_io(char *s);
int	is_pipe(char c);
int	ft_is_builtin(char *command);

// Token Utils
int			get_word_length(const char *s);
int			simple_word_length(const char *s);
char		*get_token_value(char *input);
t_token		*create_token(enum e_token_type type, char *value, int i);

#endif