/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:30:15 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/23 16:06:24 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(t_cmd *cmd)
{
	int	len;

	len = builtin_cmd_len(cmd->name);
	printf("{%s} is in ft_is_builtin with len {%d}\n", cmd->name, len);
	if (ft_strncmp(cmd->name, "echo", len) == 0 && len == 4)
	{
		ft_echo(cmd->args);
		return (1);
	}
	else if (ft_strncmp(cmd->name, "env", len) == 0 && len == 3)
		return (1);
	else if (ft_strncmp(cmd->name, "pwd", len) == 0 && len == 3)
	{
		ft_pwd();
		return (1);
	}
	else if (ft_strncmp(cmd->name, "cd", len) == 0 && len == 2)
		return (1);
	else if (ft_strncmp(cmd->name, "export", len) == 0 && len == 6)
		return (1);
	else if (ft_strncmp(cmd->name, "unset", len) == 0 && len == 5)
		return (1);
	else if (ft_strncmp(cmd->name, "exit", len) == 0 && len == 4)
		return (1);
	else if (ft_strncmp(cmd->name, "getenv", len) == 0 && len == 6)
		return (1);
	return (0);
}

int	exec_builtins(char **args)
{
	int		len;

	len = builtin_cmd_len(args[0]);
	if (ft_strncmp(args[0], "echo", len) == 0)
		ft_echo(args);
	else if (ft_strncmp(args[0], "env", len) == 0)
		ft_env(g_data->env);
	else if (ft_strncmp(args[0], "pwd", len) == 0)
		{ft_pwd(); return (1);}
	else if (ft_strncmp(args[0], "cd", len) == 0)
		g_data->env = ft_cd(g_data->env, args);
	else if (ft_strncmp(args[0], "export", len) == 0)
		g_data->env = exec_export(args);
	else if (ft_strncmp(args[0], "unset", len) == 0)
		g_data->env = ft_unset(g_data->env, args);
	else if (ft_strncmp(args[0], "exit", len) == 0)
		exec_exit(args);
	else if (ft_strncmp(args[0], "getenv", len) == 0)
		printf("%s\n", ft_getenv(g_data->env, args[1]));
	return (0);
}

int	exec_exit(char **args)
{
	ft_freeptr(g_data->env);
	ft_freeptr(args);
	// free everything everywhere all at once
	exit(0);
}

char	**exec_export(char **args)
{
	if (args[1] == NULL)
		ft_export_export(g_data->env);
	else
		g_data->env = ft_export(g_data->env, args);
	return (g_data->env);
}

int	builtin_cmd_len(char *cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && cmd[len] != ' ')
		len++;
	return (len);
}
