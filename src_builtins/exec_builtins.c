/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:30:15 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/11 00:33:47 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtins(char *cmd)
{
	char	**args;
	int		len;

	args = ft_split(cmd, ' ');
	len = builtin_cmd_len(cmd);
	if (ft_strncmp(args[0], "echo", len) == 0)
		ft_echo(args);
	else if (ft_strncmp(args[0], "env", len) == 0)
		ft_env(g_data->env);
	else if (ft_strncmp(args[0], "pwd", len) == 0)
		ft_pwd();
	else if (ft_strncmp(args[0], "cd", len) == 0)
		g_data->env = ft_cd(g_data->env, args);
	else if (ft_strncmp(args[0], "export", len) == 0)
		g_data->env = exec_export(args);
	else if (ft_strncmp(args[0], "unset", len) == 0)
		g_data->env = ft_unset(g_data->env, args);
	else if (ft_strncmp(args[0], "exit", len) == 0)
		exec_exit(args, cmd);
	else if (ft_strncmp(args[0], "getenv", len) == 0)
		ft_printf("%s\n", ft_getenv(g_data->env, args[1]));
	return (0);
}

int	exec_exit(char **args, char *cmd)
{
	ft_freeptr(g_data->env);
	ft_freeptr(args);
	free(cmd);
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
