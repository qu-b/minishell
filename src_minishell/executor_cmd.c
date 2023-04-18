
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

// Find PATH in env
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
	execve(command, cmd->args, g_data->env);
	write(STD_ERR, "minishell: ", 11);
	write(STD_ERR, cmd->name, ft_strlen(cmd->name));
	write(STD_ERR, ": command not found\n", 20);
	exit(127);
}

// Set IO redirection as needed
int	set_in_out(t_token **tokens, int *tmpfd)
{
	if ((*tokens) && (*tokens)->type == IO)
	{
		if ((*tokens)->len == 1 && (*tokens)->value[0] == '<')
		{
			if (open_infile(*tokens, tmpfd))
				return (1);
		}
		else
		{
			if (open_outfile(*tokens, tmpfd))
				return (1);
		}
	}
	(*tokens) = (*tokens)->next;
	return (0);
}

// checks for builtins that are executable in a pipe
int builtin_pipe(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->name, "pwd", ft_strlen(cmd->name)))
	{
		ft_pwd();
		return (1);
	}
	else if (!ft_strncmp(cmd->name, "env", ft_strlen(cmd->name)))
	{
		ft_env(g_data->env);
		return (1);
	}
	else if (!ft_strncmp(cmd->name, "echo", ft_strlen(cmd->name)))
	{
		ft_echo(cmd->args);
		return (1);
	}
	else if (!ft_strncmp(cmd->name, "getenv", ft_strlen(cmd->name)))
	{
		printf("%s\n", ft_getenv(g_data->env, cmd->args[1]));
		return (1);
	}
	return (0);
}

// Execution command
// include ft_is_builtin + builtin execution on fork here
int	exec_cmd(t_cmd *cmd, t_token *current, t_token *last, int tmpfd)
{
	dup2(tmpfd, 0);
	close(tmpfd);
	while (current != last && current)
		if (set_in_out(&current, &tmpfd))
			return (1);
	if (builtin_pipe(cmd))
		return (0);
	else
		exec(cmd, g_data->env);
	return (0);
}
