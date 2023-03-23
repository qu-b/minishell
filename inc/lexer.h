/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:31:42 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/23 18:14:19 by fcullen          ###   ########.fr       */
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
	SQSTR,
	DQSTR,
	IO,
	PIPE,
	ENV_VAR,
	EXIT
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
}	t_token;

// Utils
int	is_space(char c);
int	is_io(char *s);
int is_pipe(char c);
int	ft_is_builtin(char *command);
int	ft_is_valid_command(char *command);

#endif