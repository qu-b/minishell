/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:22:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/17 19:12:23 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_process(void)
{
	int	status;

	while (waitpid(-1, &status, 0) != -1)
		continue ;
	if (errno == ECHILD && WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

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

	head = *tokens;
	name = malloc(sizeof(char *));
	if (!name)
		return (NULL);
	name = "";
	while (head)
	{
		if (head && head->type == WORD)
		{
			name = ft_strjoin(name, head->value);
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
	tmp = head;
	while (tmp && tmp->type != PIPE && tmp->type != IO)
	{
		i++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (i + 2));
	if (!args)
		return (NULL);
	i = 0;
	while (head && head->type != PIPE && head->type != IO)
	{
		if (!head->value)
			break ;
		args[i] = ft_strdup(head->value);
		head = head->next;
		i++;
	}
	if (i == 0)
	{
		args[0] = g_data->cmd.name;
		args[1] = NULL;
	}
	else
		args[i] = NULL;
	return (args);
}

// Gets final element of a command.
// To know whether or not to start/continue pipeline execution.
t_token	*get_last_cmd(t_token *current)
{
	t_token	*last_cmd = NULL;

	if (current)
		while (current->next)
		{
			if (current->type == PIPE)
				last_cmd = current;
			current = current->next;
		}
	if (!last_cmd)
		last_cmd = current;
	return (last_cmd);
}

// Set IO redirection as needed
int	set_in_out(t_token **tokens, int *tmpfd)
{
	int	is_io = 0;

	if ((*tokens) && (*tokens)->type == IO)
	{
		if ((*tokens)->len == 1 && (*tokens)->value[0] == '<')
			open_infile(*tokens, tmpfd);
		else
			open_outfile(*tokens, tmpfd);
		is_io = 1;
	}
	(*tokens) = (*tokens)->next;
	return (is_io);
}

// Free command
void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->name)
		{
			free(cmd->name);
			cmd->name = NULL;
		}
		if (cmd->args)
		{
			double_free(cmd->args);
			cmd->args = NULL;
		}
	}
}

// Main parser function
int	parse_cmd(t_token **tokens, int pid_i)
{
	t_cmd	*cmd;
	t_token	*last = NULL;

	cmd = &(g_data->cmd);
	cmd->name = get_name(tokens);
	cmd->args = get_args(*tokens);
	last = get_last_cmd(*tokens);
	cmd->heredoc = 0;
	// heredoc(tokens, cmd, pid_i);
	if (last && last->type == PIPE)
	{
		if (exec_pipe(cmd, tokens, pid_i))
			return (1);
	}
	// else if (ft_is_builtin(cmd->name))
	// {
	// 	if (exec_builtins(cmd->args))
	// 	// if ((*tokens) != NULL)
	// 	// 	(*tokens) = (*tokens)->next;
	// 		return (1);
	// }
	else 
	{
		if (exec_main(cmd, tokens, pid_i, cmd->tmpfd))
			return (1);
	}
	*tokens = last->next;
	// free_cmd(cmd);
	return (0);
}

int	executor(t_token **head)
{
	int	i;
	int	pid_i;

	i = 0;
	pid_i = 0;
	g_data->cmd.tmpfd = dup(0);
	g_data->pid = malloc(sizeof(pid_t) * get_n_cmds(*head));
	if (!g_data->pid)
		return (1);
	while ((*head) && (*head)->value)
	{
		if (parse_cmd(head, pid_i++))
			break ;
	}
	wait_process();
	free(g_data->pid);
	show_ctrl_disable();
	g_data->ext = 0;
	return (0);
}
