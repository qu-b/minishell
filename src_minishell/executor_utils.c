
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:10:01 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/21 11:17:06 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char **envp)
{
	while (envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

// Return accessible command path if possible
char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(command, F_OK))
			return (command);
		free(command);
		paths++;
	}
	return (cmd);
}

// Execute a binary using get_cmd to find full path
int	exec(t_cmd *cmd, char **envp)
{
	char	**paths;
	char	*envpath;
	char	*command;

	envpath = find_path(envp);
	paths = ft_split(envpath, ':');
	command = get_cmd(paths, cmd->name);
	if (execve(command, cmd->args, g_data->env))
		return (1);
	write(STD_ERR, "minishell: ", 11);
	write(STD_ERR, cmd->name, ft_strlen(cmd->name));
	write(STD_ERR, ": command not found\n", 20);
	exit(127);
}

// Execution command
// include ft_is_builtin + builtin execution on fork here
int	exec_cmd(t_cmd *cmd, t_token *current, t_token *last, int tmpfd)
{
	dup2(tmpfd, 0);
	close(tmpfd);
	while (current != last && current)
		set_in_out(&current, &tmpfd);
	// if (ft_is_builtin)
		// if (exec_builtin)
			// return (1);
	exec(cmd, g_data->env);
	return (0);
}

// Execute on main process
// probably check builtin + execute builtin on main here
int	exec_main(t_cmd *cmd, t_token **current, int pid_i, int tmpfd)
{
	(void)tmpfd;
	g_data->pid[pid_i] = fork();
	show_ctrl_enable();
	// if (!ft_is_builtin)
	// run this:
	if (!g_data->pid[pid_i])
	{
		dup2(tmpfd, 0);
		close(tmpfd);
		exec_cmd(cmd, *current, get_last_cmd(*current), cmd->tmpfd);
		exit(0);
	}
	close(cmd->tmpfd);
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
		exec_cmd(cmd, *current, get_last_cmd(*current), cmd->tmpfd);
		exit(1);
	}
	*current = (*current)->next;
	return (0);
}
