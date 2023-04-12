
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
	write(STD_ERR, "minishell: ", 11);
	write(STD_ERR, args[0], ft_strlen(args[0]));
	write(STD_ERR, ": command not found\n", 20);
	exit(127);
}

void	exec_bin(char *cmd, char **env, int fdin)
{
	if (!cmd[1])
		return ;
	pid_t	pid;
	// int		pipefd[2];
	(void)fdin;
	// pipe(pipefd);
	pid = fork();
	// printf("pid: %d\n", g_data->pid);
	show_ctrl_enable();
	if (pid)
	{
		g_data->ext = 1;
		// close(pipefd[1]);
		// dup2(pipefd[0], STD_IN);
		waitpid(pid, 0, 0);
		show_ctrl_disable();
		g_data->ext = 0;
	}
	else
	{
		// close(pipefd[0]);
		// dup2(pipefd[1], STD_OUT);
		// if (fdin == STD_IN)
		// 	exit(1);
		// else
			exec(cmd, env);
	}
}

void	exec_pipe(char *cmd, char **env, int fdin, int fdout)
{
	pid_t	pid;
	int		pipefd[2];
	(void)fdin;
	(void)fdout;
	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], fdin);
		waitpid(pid, 0, 0);
	}
	else
	{
		close(g_data->pipefd[0]);
		dup2(g_data->pipefd[1], fdout);
		// if (fdin != STD_IN)
		// 	dup2(fdin, STD_IN);
		exec(cmd, env);
	}
}

// int	exec_pipe(int ac, char **av, char **envp)
// {
// 	int	fdin;
// 	int	fdout;
// 	int	i;

// 	i = 2;
// 	if (ac >= 5)
// 	{
// 		fdin = openfile(av[1], INFILE);
// 		fdout = openfile(av[ac - 1], OUTFILE);
// 		dup2(fdin, STD_IN);
// 		dup2(fdout, STD_OUT);
// 		redirect(av[2], envp, fdin);
// 		while (++i < ac - 2)
// 			redirect(av[i], envp, fdin);
// 		exec(av[i], envp);
// 	}
// 	else
// 		write(STD_ERR, "Invalid number of arguments.\n", 29);
// 	return (1);
// }
