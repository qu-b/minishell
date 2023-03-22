/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:31:42 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/22 17:03:46 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Define Tokens
#define TOK_COMMAND 1
#define TOK_ARGUMENT 2
#define TOK_OPERATOR 3
#define TOK_REDIRECTION 4
#define TOK_PIPE 5
#define TOK_BACKGROUND 6
#define TOK_NEWLINE 7
#define TOK_EOF 8

typedef struct s_token
{
	int type;
	char *value;
} t_token;


// Utils
int	ft_isspace(char c);
