/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:14:07 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/25 17:05:04 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Checks string for command + argument
t_token *cmd_arg_lexer(enum e_token_type type, char *input)
{
	char	*value;

	value = get_token_value(input);
	if (!value)
		return (NULL);
	return (create_token(type, value, ft_strlen(value)));
}

t_token	*lexer(char *input)
{
	int		i;
	int		n;
	int		len;
	enum e_token_type type;
	t_token	*tokens;

	i = 0;
	(void) i;
	(void) type;
	n = 0;
	len = ft_strlen(input);
	// printf("%d\n", is_io(&input[i]));
	tokens = malloc(sizeof(t_token) * (len + 1));
	type = CMD;
	while (input && n < len)
	{
		if (*input == '\0' )
			break ;
		// Skip whitespace
		while (is_space(*input))
			input++;
		// Tokenize IO + pipe
		if (is_io(input) > 0)
		{
			tokens[n] = *create_token(IO, input, is_io(input));
			input += is_io(input);
			n++;
		}
		else if (is_pipe(*input))
		{
			tokens[n] = *create_token(PIPE, input, 1);
			input++;
			n++;
		}
		// Tokenize Command + Arg
		else if (ft_isalpha(*input) || *input == '-' || *input == '\'' || *input == '\"')
		{
			if (*input == '-')
				tokens[n] = *cmd_arg_lexer(ARG, input);
			else if (*input == '\'' || *input == '\"')
				tokens[n] = *cmd_arg_lexer(STR, input);
			else
				tokens[n] = *cmd_arg_lexer(CMD, input);
			input += tokens[n].len;
			n++;
		}
		// Tokenize Environment variable
		else if (*input == '$')
		{
			tokens[n] = *create_token(VAR, input + 1, simple_word_length(input + 1));
			input += tokens[n].len + 1;
			n++;
		}
		// Tokenize Path
		else if (*input == '/')
		{
			tokens[n] = *create_token(PATH, get_token_value(input), simple_word_length(input));
			input += tokens[n].len;
			n++;
		}
		else
			input++;
	}
	tokens[n].value = NULL;
	return (tokens);
}
