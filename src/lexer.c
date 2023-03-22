/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:14:07 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/22 16:44:25 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	check_token(t_token	token, char c)
// {

// }

t_token *tokenize(char *input)
{
	int		i;
	int		n;
	int		len;
	t_token	*tokens;

	i = 0;
	n = 0;
	len = ft_strlen(input);
	tokens = malloc(sizeof(t_token) * len);
	while (input[i])
	{
		// Skip whitespace
		if (ft_isspace(input[i++]))
			continue;
		// Check operators
		if (input[i] == '>' || input[i] == '<') 
		{
			tokens[n].type = TOK_REDIRECTION;
			tokens[n].value = malloc(sizeof(char) * 2);
			tokens[n].value[0] = input[i];
			tokens[n].value[1] = '\0';
			n++;
			i++;
			continue;
		}
	}
	return (tokens);
}
