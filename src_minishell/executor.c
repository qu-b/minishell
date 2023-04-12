/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:22:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/12 19:28:26 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Function to get command + args as a string
char *get_args(t_token **head)
{
	char	*args;

	args = malloc(sizeof(char *));
	if (!args)
		return (NULL);
	args = "";
	while (*head && (*head)->type != PIPE && (*head)->type != IO)
	{
		if (!(*head)->value)
			return NULL;
		args = ft_strjoin(args, (*head)->value);
		args = ft_strjoin(args, " ");
		(*head) = (*head)->next;
	}
	return (args);
}

// Function to get command + args directly as a str pointer
char **get_args_ptr(t_token **head)
{
	char	**args;
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = *head;
	while (tmp && tmp->type != PIPE && tmp->type != IO)
	{
		i++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	args[i] = NULL;
	i = 0;
	while (*head && (*head)->type != PIPE && (*head)->type != IO)
	{
		if (!(*head)->value)
			return NULL;
		args[i] = ft_strdup((*head)->value);
		(*head) = (*head)->next;
		i++;
	}
	return (args);
}

int	parse_cmd(t_token *tokens)
{
	t_token	*head;
	char	*args;
	// split(args, ' ') in exec fails when args[n] was parsed as string literal
	char	**dargs; // ready for exec, need to change pipex, idk how, help
	int		fdin;
	int		fdout;
	int		mfd;

	(void) mfd;
	head = tokens;
	fdin = 0;
	fdout = 1;
	args = NULL;
	dargs = NULL;
	// for (int i = 0; i < 5; i++)
	// 	printf("%s\n", g_data->env[i]);
	while (head)
	{
		if (head->type == IO && head->len == 1)
		{
			if (head->value[0] == '<')
				fdin = openfile(head->next->value, 0);
			else
				fdout = openfile(head->next->value, 1);
			mfd = fdout;
		}
		// else if (head->type == PIPE)
		if (head->next && head->next->type == PIPE)
		// execute into a pipe linked to the data struct
		// `g_data->pipe[2]`;
		{
			args = get_args(&head);
			// if (args == NULL)
			// 	return (0);
			head = head->next;
			// printf("%s\n", args);
			exec_pipe(args, g_data->env, fdin, fdout);
			head = head->next;
		}
		else if (ft_is_builtin(head->value))
		{
			dargs = get_args_ptr(&head);
			exec_builtins(dargs);
		}
		else
		{
			args = get_args(&head);
			// printf("%s\n", head->value);
			// exec(args, g_data->env);
			redirect(args, g_data->env, fdin);
			// head = head->next;
		}
	}
	if (args)
		free(args);
	if (dargs)
		ft_freeptr(dargs);
	return (0);
}

int	executor(t_token *tokens)
{
	if (parse_cmd(tokens))
		return (1);
	return (0);
}
