/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:14:07 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/23 19:27:32 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Checks string for argument
t_token	*lex_arg(t_token *token, char *input)
{
	int		j;
	char	*arg;

	j = 1;
	while (ft_isalpha(input[j]) && input[j])
		j++;
	arg = malloc(sizeof(char) * (j + 2));
	ft_strlcpy(arg, input, j + 1);
	arg[j] = '\0';
	token->type = ARG;
	token->value = arg;
	return (token);
}

// Checks string for a command
t_token	*lex_cmd(t_token *token, char *input)
{
	int		j;
	char	*command;

	j = 0;
	if (ft_isalpha(*input))
	{
		while (ft_isalpha(input[j]) && input[j])
			j++;
		command = malloc(sizeof(char) * (j + 1));
		ft_strlcpy(command, input, j + 1);
		command[j] = '\0';
		token->type = CMD;
		token->value = command;
	}
	return (token);
}

t_token	*lexer(char *input)
{
	int		i;
	int		n;
	int		len;
	t_token	*tokens;

	i = 0;
	n = 0;
	len = ft_strlen(input);
	tokens = malloc(sizeof(t_token) * len);
	while (input)
	{
		if (*input == '\0')
			break ;
		// Skip whitespace
		while (is_space(*input))
			input++;
		// Check IO
		if ((*input == '<' && *input + 1 == '<')
			|| (*input == '>' && *input + 1 == '>'))
		{
			tokens[n].type = IO;
			tokens[n].value = malloc(sizeof(char) * 3);
			tokens[n].value[0] = *input;
			tokens[n].value[1] = *input + 1;
			tokens[n].value[2] = '\0';
			input += 2;
			n++;
		}
		// Check IO + pipe
		else if (*input == '<' || *input == '>' || is_pipe(*input))
		{
			tokens[n].type = IO;
			tokens[n].value = malloc(sizeof(char) * 2);
			tokens[n].value[0] = *input;
			tokens[n].value[1] = '\0';
			input += 1;
			n++;
		}
		// Check Command
		else if (ft_isalpha(*input))
		{
			lex_cmd(&tokens[n], input);
			n++;
			while (ft_isalpha(*input))
				input++;
		}
		// Check Arg
		else if (*input == '-')
		{
			lex_arg(&tokens[n], input);
			input++;
			while (ft_isalpha(*input))
					input++;
			n++;
		}
		// Check Pipe
		// Check Env Var
		else
			input++;
	}
	return (tokens);
}
