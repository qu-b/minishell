/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:23:01 by zaphod           #+#    #+#             */
/*   Updated: 2023/04/28 12:47:15 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Get number of commands
int	get_n_cmds(t_token *tokens)
{
	int	n;

	n = 0;
	if (tokens->type != PIPE)
		n++;
	while (tokens)
	{
		if (tokens->type == PIPE)
			n++;
		tokens = tokens->next;
	}
	return (n);
}

// Function to get command name
char	*get_name(t_token **tokens)
{
	char	*name;
	t_token	*head;

	if (!tokens || (*tokens)->value == NULL)
		return (NULL);
	head = *tokens;
	name = malloc(sizeof(char *));
	if (!name)
		return (NULL);
	name[0] = '\0';
	while (head)
	{
		if (head && head->type == WORD)
		{
			name = ft_strjoin_gnl(name, head->value);
			name = ft_strtrim_free(name, " ");
			return (name);
		}
		if (head->type == IO)
			head = head->next;
		if (head)
			head = head->next;
	}
	return (name);
}

// Function to get command args
char	**get_args(t_token *head)
{
	char	**args;
	int		i;
	t_token	*tmp;

	i = 0;
	if (!ft_strncmp(head->value, "<", 1))
		head = head->next->next;
	tmp = head;
	while (tmp && tmp->type != PIPE && tmp->type != IO && ++i)
		tmp = tmp->next;
	args = malloc(sizeof(char *) * (i + 2));
	if (!args)
		return (NULL);
	i = 0;
	while (head && head->type != PIPE && head->type != IO)
	{
		args[i] = ft_strdup(head->value);
		i++;
		head = head->next;
	}
	if (i == 0)
		args[i++] = ft_strdup(head->value);
	args[i] = NULL;
	return (args);
}

// Gets final element of a command.
// To know whether or not to start/continue pipeline execution.
t_token	*get_last_cmd(t_token *current)
{
	if (!current)
		return (NULL);
	while (current->next)
	{
		if (current->type == PIPE)
			return (current);
		current = current->next;
	}
	return (current);
}
