/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:28:26 by fcullen           #+#    #+#             */
/*   Updated: 2023/05/10 11:44:19 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checks for builtin that cannot be executed if not at start
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

// checks for builtins that are executable in a pipe
int	builtin_pipe(t_cmd *cmd)
{
	int	len;

	len = ft_strlen(cmd->name);
	if (!ft_strncmp(cmd->name, "pwd", len) && len == 3)
	{
		ft_pwd();
		return (1);
	}
	else if (!ft_strncmp(cmd->name, "env", len) && len == 3)
	{
		ft_env(g_data->env);
		return (1);
	}
	else if (!ft_strncmp(cmd->name, "echo", len) && len == 4)
	{
		ft_echo(cmd->args);
		return (1);
	}
	return (0);
}
