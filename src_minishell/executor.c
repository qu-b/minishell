/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:22:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/30 17:36:41 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_args(t_token *token)
{
	char *args;
	int i;

	args = malloc(sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	args = "";
	while (token && token->type != PIPE && token->type != IO)
	{
		args = ft_strjoin(args, token->value);
		args = ft_strjoin(args, " ");
		token = token->next;
	}
	printf("%s\n", args);
	return (args);
}

int	parse_cmd(t_data *data, t_token *tokens)
{
	t_token	*head;
	char	*args;
	int		fdin;
	int		fdout;

	head = tokens;
	// for (int i = 0; i < 5; i++)
	// 	printf("%s\n", data->env[i]);
	while (head)
	{
		if (head->type == IO && head->len == 1)
		{
			if (head->value[0] == '<')
				fdin = openfile(head->next->value, 0);
			else
				fdout = openfile(head->next->value, 1);
		}
		else if (head->type != PIPE)
		{
			args = get_args(head);
			exec(args, data->env);
		}
		// else
		// {
		// 	exec_pipe(args, data->env);
		// }
		head = head->next;
	}
	return (0);
}

int	executor(t_data *data, t_token *tokens)
{
	if (parse_cmd(data, tokens))
		return (1);
	return (0);
}