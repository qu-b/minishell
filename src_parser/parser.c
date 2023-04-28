/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:44:16 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/12 17:55:49 by fcullen          ###   ########.fr       */
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
	new_token->value = value;
	new_token->type = type;
	new_token->len = len;
	new_token->next = NULL;
	return (new_token);
}

int	add_token(t_token **head, enum e_token_type type, char *value, int len)
{
	char	*tmp;
	t_token	*new_token;
	t_token	*current;

	new_token = create_token(type, NULL, len);
	tmp = ft_strtrim_free(value, " ");
	new_token = create_token(type, tmp, len);
	if (!new_token)
	{
		free(tmp);
		return (1);
	}
	if (!(*head))
	{
		*head = new_token;
		return (0);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
	return (0);
}

int	tokenizer(t_token **head, char *s, int *i)
{
	int		len;

	if (!s)
		return (add_token(head, 0, NULL, 1));
	else if (is_pipe(*s))
	{
		*i += 1;
		return (add_token(head, PIPE, ft_substr(s, 0, 1), 1));
	}
	else if (is_io(s))
	{
		*i += is_io(s);
		return (add_token(head, IO, ft_substr(s, 0, is_io(s)), is_io(s)));
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

int	parser(char *input)
{
	t_token	*head;

	if (!lexer(&head, input))
		process_tokens(head);
	else
		return (1);
	g_data->tokens = head;
	return (0);
}
