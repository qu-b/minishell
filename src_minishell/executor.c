/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:22:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/19 10:14:02 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Wait for all children
int	wait_process(void)
{
	int	status;

	while (waitpid(-1, &status, 0) != -1)
		continue ;
	if (errno == ECHILD && WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

// Execute on pipe
int	exec_pipe(t_cmd *cmd, t_token **current, int pid_i)
{
	printf("Hi from pipe with {%s}\n", cmd->name);
	pipe(cmd->pipe);
	g_data->pid[pid_i] = fork();
	if (g_data->pid[pid_i] == -1)
		return (1);
	show_ctrl_enable();
	if (g_data->pid[pid_i])
	{
		close(cmd->tmpfd);
		cmd->tmpfd = cmd->pipe[0];
		close(cmd->pipe[1]);
	}
	else
	{
		dup2(cmd->pipe[1], 1);
		close(cmd->pipe[1]);
		close(cmd->pipe[0]);
		exec_cmd(cmd, *current, get_last_cmd(*current), cmd->tmpfd);
		exit(1);
	}
	// *current = (*current)->next;
	// printf("Next is {%s}\n", (*current)->value);
	return (0);
}

// checks for builtin that cannot be executed if not at start
// ls | export hi=HELLOOO | echo $hi does nothing in bash
int	builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->name, "cd", ft_strlen(cmd->name)))
	{
		g_data->env = ft_cd(g_data->env, cmd->args);
		return (1);
	}
	else if (!ft_strncmp(cmd->name, "export", ft_strlen(cmd->name)))
	{
		g_data->env = exec_export(cmd->args);
		return (1);
	}
	else if (!ft_strncmp(cmd->name, "unset", ft_strlen(cmd->name)))
	{
		g_data->env = ft_unset(g_data->env, cmd->args);
		return (1);
	}
	else if (!ft_strncmp(cmd->name, "exit", ft_strlen(cmd->name)))
	{
		exec_exit(cmd->args);
		return (1);
	}
	return (0);
}

// Execute on main process
// probably check builtin + execute builtin on main here
int	exec_main(t_cmd *cmd, t_token **current, int pid_i, int tmpfd)
{
	(void)tmpfd;
	show_ctrl_enable();
	if (!builtin(cmd))
	{
		g_data->pid[pid_i] = fork();
		if (!g_data->pid[pid_i])
		{
			dup2(tmpfd, 0);
			close(tmpfd);
			exec_cmd(cmd, *current, get_last_cmd(*current), cmd->tmpfd);
			exit(0);
		}
	}
	close(cmd->tmpfd);
	return (0);
}

// Main parser function
int	parse_cmd(t_token **tokens, int pid_i)
{
	t_cmd	*cmd;
	t_token	*last = NULL;

	if (!ft_strncmp((*tokens)->value, "", 1))
		return (1);
	cmd = &(g_data->cmd);
	cmd->name = get_name(tokens);
	cmd->args = get_args(*tokens);
	last = get_last_cmd(*tokens);
	cmd->heredoc = 0;
	// heredoc(tokens, cmd, pid_i);
	printf("Last is {%s}\n", last->value);
	if (last && last->type == PIPE)
	{
		if (exec_pipe(cmd, tokens, pid_i))
			return (1);
	}
	else 
	{
		if (exec_main(cmd, tokens, pid_i, cmd->tmpfd))
			return (1);
	}
	*tokens = last->next;
	free_cmd(cmd);
	// free_cmd(&g_data->cmd);
	return (0);
}

int	executor(void)
{
	int	i;
	int	pid_i;
	t_token *head;

	i = 0;
	pid_i = 0;
	head = g_data->tokens;
	g_data->cmd.tmpfd = dup(0);
	g_data->pid = malloc(sizeof(pid_t) * get_n_cmds(head));
	if (!g_data->pid)
		return (1);
	while ((head) && (head)->value)
	{
		if (parse_cmd(&head, pid_i++))
			break ;
	}
	wait_process();
	free(g_data->pid);
	show_ctrl_disable();
	g_data->ext = 0;
	return (0);
}
