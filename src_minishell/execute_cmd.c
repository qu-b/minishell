/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:45:41 by zaphod           #+#    #+#             */
/*   Updated: 2023/05/10 14:24:10 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Find PATH in env
char	*find_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp("PATH", *envp, 4) == 0)
			return (*envp + 5);
		envp++;
	}
	write(STDERR_FILENO, "minishell: PATH does not exist\n", 31);
	exit(127);
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
int	set_in_out(t_token **tokens, t_cmd *cmd, int *tmpfd)
{
	if ((*tokens) && (*tokens)->type == IO)
	{
		if ((*tokens)->value[0] == '<')
		{
			if ((*tokens)->len == 1 && open_infile(*tokens, tmpfd))
				return (1);
			else if (heredoc(tokens, cmd))
				return (1);
		}
		else if (open_outfile(*tokens, tmpfd))
			return (1);
	}
	(*tokens) = (*tokens)->next;
	if ((*tokens)->type == IO && !(*tokens)->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		exit(258);
	}
	else
		return (0);
}

// Execution command
// include ft_is_builtin + builtin execution on fork here
int	exec_cmd(t_cmd *cmd, t_token *current, t_token *last, int tmpfd)
{
	dup2(tmpfd, 0);
	close(tmpfd);
	while (current != last && current)
		if (set_in_out(&current, cmd, &tmpfd))
			return (1);
	if (builtin_pipe(cmd))
		return (0);
	exec(cmd, g_data->env);
	free_cmd(&g_data->cmd);
	return (0);
}
