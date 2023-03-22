/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:14:07 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/22 21:25:03 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	check_token(t_token	token, char c)
// {

// }


t_token	*lex_cmd(t_token* tokens, char* input, int* num_tokens, int c) 
{
	int		i;
	int		j;
	int		len;
	int		n;
	char*	command;

	i = 0;
	j = 0;
	len = 0;
	n = 0;
	if (ft_isalpha(input[c])) 
	{
		j = c + 1;
		while (ft_isalpha(input[j]))
			j++;
		len = j - c;
		command = malloc(sizeof(char) * (len + 2));
		ft_strlcpy(command, &input[c], len + 1);
		command[len] = '\0';
		tokens[n].type = TOK_COMMAND;
		tokens[n].value = command;
		n++;
	}
	*num_tokens = n;
	return tokens;
}

t_token *lexer(char *input)
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
		while (ft_isspace(input[i]))
			i++;
		// Check Command
		if (ft_isalpha(input[i]) || (input[i - 1] && (input[i - 1] != '\'' || input[i - 1] != '\"'))) 
		{
				lex_cmd(&tokens[n], input, &n, i);
				while (ft_isalpha(input[i]))
					i++;
		}
		// Check Arg
		// Check Redirections
		else if (input[i] == '>' || input[i] == '<') 
		{
			tokens[n].type = TOK_REDIRECTION;
			tokens[n].value = malloc(sizeof(char) * 2);
			tokens[n].value[0] = input[i];
			tokens[n].value[1] = '\0';
			n++;
			i++;
			// continue;
		}
		// Check Pipe
		// Check Env Var
		if (input[i] == '\0')
			break ;
		i++;
	}
	return (tokens);
}
