/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:44:16 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/03 12:11:20 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(enum e_token_type type, char *value, int len)
{
	t_token	*new_token;

	if (len < 0)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = malloc(sizeof(char) * (ft_strlen(value) + 1));
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	ft_strlcpy(new_token->value, value, len + 1);
	new_token->len = len;
	new_token->next = NULL;
	return (new_token);
}

int	add_token(t_token **head, enum e_token_type type, char *value, int len)
{
	t_token	*newtoken;
	t_token	*current;

	newtoken = create_token(type, value, len);
	if (!newtoken)
		return (1);
	if (!(*head))
	{
		*head = newtoken;
		return (0);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = newtoken;
	return (0);
}

int	tokenizer(t_token **head, char *s, int *i)
{
	int	len;

	if (!s)
		return (add_token(head, 0, 0, 1));
	else if (is_pipe(*s))
	{
		*i += 1;
		return (add_token(head, PIPE, ft_substr(s, 0, 1), 1));
	}
	else if (is_io(s))
	{
		*i += is_io(s);
		return (add_token(head, IO,
				ft_substr(s, 0, is_io(s)), is_io(s)));
	}
	else if (find_space(s))
	{
		len = str_length(s);
		if (len < 0)
			return (1);
		*i += len;
		return (add_token(head, WORD, ft_substr(s, 0, len), len));
	}
	return (0);
}

int	lexer(t_token **head, char *s)
{
	int		i;
	int		error;

	*head = NULL;
	i = 0;
	while (*(s + i) == ' ')
		i++;
	error = tokenizer(&(*head), s + i, &i);
	if (error)
		return (1);
	while (i < (int)ft_strlen(s))
	{
		if (*(s + i) != ' ')
		{
			error = tokenizer(&(*head), s + i, &i);
			if (error)
				return (1);
		}
		else
			i++;
	}
	return (0);
}
