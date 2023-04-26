/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:22:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/26 14:59:01 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Wait for all children
int	wait_child(void)
{
	int	status;

	while (waitpid(-1, &status, 0) != -1)
		continue ;
	if (errno == ECHILD && WIFEXITED(status))
	{
		g_data->ext = 0;
		return (WEXITSTATUS(status));
	}
	g_data->ext = 0;
	return (0);
}

// Execute on pipe
int	exec_pipe(t_cmd *cmd, t_token **current, int pid_i)
{
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
		// g_data->ext = 1;
		exec_cmd(cmd, *current, get_last_cmd(*current), cmd->tmpfd);
		exit(1);
	}
	return (0);
}

// checks for builtin that cannot be executed if not at start
// ls | export hi=HELLOOO | echo $hi does nothing in bash
int	builtin(t_cmd *cmd)
{
	int	len;

	len = ft_strlen(cmd->name);
	if (!ft_strncmp(cmd->name, "cd", len) && len == 2)
	{
		g_data->env = ft_cd(g_data->env, cmd->args);
		return (1);
	}
	else if (!ft_strncmp(cmd->name, "export", len) && len == 6)
	{
		g_data->env = exec_export(cmd->args);
		return (1);
	}
	else if (!ft_strncmp(cmd->name, "unset", len) && len == 5)
	{
		g_data->env = ft_unset(g_data->env, cmd->args);
		return (1);
	}
	else if (!ft_strncmp(cmd->name, "exit", len) && len == 4)
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
		g_data->ext = 1;
		if (!g_data->pid[pid_i])
		{
			dup2(tmpfd, 0);
			close(tmpfd);
			exec_cmd(cmd, *current, get_last_cmd(*current), tmpfd);
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
	heredoc(tokens, cmd);
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
	int	pid_i;
	t_token *head;

	pid_i = 0;
	head = g_data->tokens;
	g_data->cmd.tmpfd = dup(0);
	g_data->pid = malloc(sizeof(pid_t) * get_n_cmds(head));
	if (!g_data->pid)
		return (1);
	while ((head) && (head)->value)
	{
		g_data->ext = 0;
		if (parse_cmd(&head, pid_i++))
			break ;
	}
	g_data->exit_status = wait_child();
	free(g_data->pid);
	show_ctrl_disable();
	return (0);
}
