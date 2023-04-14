
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
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

void	exec(t_cmd *cmd, char **envp)
{
	char	**paths;
	char	*envpath;
	char	*command;

	envpath = find_path(envp);
	paths = ft_split(envpath, ':');
	command = get_cmd(paths, cmd->name);
	execve(command, cmd->args, envp);
	write(STD_ERR, "minishell: ", 11);
	write(STD_ERR, cmd->name, ft_strlen(cmd->name));
	write(STD_ERR, ": command not found\n", 20);
	exit(127);
}

int	exec_bin(t_cmd *cmd, char **env, int pid_i, int tmpfd)
{
	g_data->pid[pid_i] = fork();
	show_ctrl_enable();
	if (!g_data->pid[pid_i])
	{
		dup2(tmpfd, 0);
		close(tmpfd);
		exec(cmd, env);
		exit(1);
	}
	close(cmd->tmpfd);
	return (0);
}

int	exec_pipe(t_cmd *cmd, char **env, int pid_i)
{
	pipe(cmd->pipe);
	g_data->pid[pid_i] = fork();
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
		exec_bin(cmd, env, pid_i, cmd->tmpfd);
		exit(0);
	}
	return (0);
}
