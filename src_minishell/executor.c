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

#include "../inc/minishell.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static char	*get_cmd(char **paths, char *cmd)
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

void	exec(char *cmd, char **envp)
{
	char	**paths;
	char	*envpath;
	char	**args;
	char	*command;

	envpath = find_path(envp);
	paths = ft_split(envpath, ':');
	args = ft_split(cmd, ' ');
	command = get_cmd(paths, args[0]);
	execve(command, args, envp);
	write(STD_ERR, "pipex: ", 7);
	write(STD_ERR, args[0], ft_strlen(args[0]));
	write(STD_ERR, ": command not found\n", 20);
	exit(127);
}

void	redirect(char *cmd, char **env, int fdin)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STD_IN);
		waitpid(pid, 0, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STD_OUT);
		if (fdin == STD_IN)
			exit(1);
		else
			exec(cmd, env);
	}
}
