/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:22:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/16 09:33:46 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to get command name
char *get_name(t_token **tokens)
{
	char	*name;
	t_token	*head;

	head = *tokens;
	name = malloc(sizeof(char *));
	if (!name)
		return (NULL);
	name = "";
	if (head && head->type != PIPE && head->type != IO)
	{
		if (!head->value)
			return (NULL);
		name = ft_strjoin(name, head->value);
		name = ft_strtrim(name, " ");
		head = head->next;
	}
	return (name);
}

// Function to get command args
char **get_args(t_token **head)
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
	args = malloc(sizeof(char *) * (i + 2));
	if (!args)
		return (NULL);
	args[0] = g_data->cmd.name;
	i = 0;
	while (*head && (*head)->type != PIPE && (*head)->type != IO)
	{
		if (!(*head)->value)
			break ;
		args[i] = ft_strtrim((*head)->value, " ");
		(*head) = (*head)->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	parse_cmd(t_token **tokens, int pid_i)
{
	t_cmd	*cmd;

	printf("%d\n", pid_i);
	cmd = &(g_data->cmd);
	cmd->name = get_name(tokens);
	cmd->args = get_args(tokens);
	check_heredoc(tokens, cmd); // doesnt work
	if ((*tokens) && (*tokens)->type == PIPE)
	{
		exec_pipe(cmd, g_data->env, pid_i);
		(*tokens) = (*tokens)->next;
		printf("pipe\n");
		return (1);
	}
	if (ft_is_builtin(cmd->name))
	{
		g_data->ext = 0;
		exec_builtins(cmd->args);
		if ((*tokens))
			(*tokens) = (*tokens)->next;
		return (1);
	}
	else if (tokens)
	{
		exec_bin(cmd, g_data->env, pid_i, cmd->tmpfd);
		return (1);
	}
	free(cmd->name);
	ft_freeptr(cmd->args);
	return (0);
}

int	wait_process(void)
{
	int		status;

	while (waitpid(-1, &status, 0) != -1)
		continue ;
	if (errno == ECHILD && WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	executor(t_token **head)
{
	int		pid_i;

	pid_i = 0;
	g_data->cmd.tmpfd = dup(0);
	g_data->pid = malloc(sizeof(pid_t) * count_pipes(head));
	g_data->ext = 1;
	while ((*head) && (*head)->value)
		parse_cmd(head, pid_i++);
	wait_process();
	free(g_data->pid);
	show_ctrl_disable();
	g_data->ext = 0;
	return (0);
}
