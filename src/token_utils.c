/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:03:05 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/24 15:34:52 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	simple_word_length(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && !is_space(s[i]))
		i++;
	return (i);
}
// Get word length with quotes (doesn't work properly yet)
int	get_word_length(const char *s)
{
	int	i;
	int	insq; // single quote flag
    int	indq; // double quote flag

	i = 0;
	insq = 0;
	indq = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !indq)
		{
			insq = !insq;
		}
		else if (s[i] == '"' && !insq) // found double quote and not in single quotes
		{
			indq = !indq; // flip double quote flag
		}
		else if (is_space(s[i]) && !insq && !indq) // found space and not in quotes
		{
			return i;
		}
		i++;
	}
	return ((insq || indq) * (-1) + (!(insq || indq)) * i);
}

// Create a new token
t_token	*create_token(enum e_token_type type, char *value, int i)
{
	t_token	*t;

	if (i < 0)
		return (NULL);
	t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->type = type;
	t->value = get_token_value(value);
	t->len = i;
	return (t);
}

// Get token value
char	*get_token_value(char *input)
{
	int		i;
	char	*value;

	i = simple_word_length(input);
	if (i == -1)
		return (NULL); // check for string length (inside quotes with get_word_length)
	value = malloc(sizeof(char) * i + 2);
	if (!value)
		return (NULL);
	ft_strlcpy(value, input, i + 1);
	value[i] = '\0';
	return (value);
}
