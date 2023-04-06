/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:30:15 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/06 05:41:35 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtins(t_data *data, char *cmd)
{
	char	**args;
	int		len;

	args = ft_split(cmd, ' ');
	len = builtin_cmd_len(cmd);
	if (ft_strncmp(args[0], "echo", len) == 0)
		ft_echo(args);
	else if (ft_strncmp(args[0], "env", len) == 0)
		ft_env(data->env);
	else if (ft_strncmp(args[0], "pwd", len) == 0)
		ft_pwd(data->env);
	else if (ft_strncmp(args[0], "cd", len) == 0)
		data->env = ft_cd(data->env, args);
	else if (ft_strncmp(args[0], "export", len) == 0)
		data->env = exec_export(data, args);
	else if (ft_strncmp(args[0], "unset", len) == 0)
		data->env = ft_unset(data->env, args);
	else if (ft_strncmp(args[0], "exit", len) == 0)
		exec_exit(data, args, cmd);
	return (0);
}

int	exec_exit(t_data *data, char **args, char *cmd)
{
	ft_freeptr(data->env);
	ft_freeptr(args);
	free(cmd);
	// free everything everywhere all at once
	exit(0);
}

char	**exec_export(t_data *data, char **args)
{
	if (args[1] == NULL)
		ft_export_export(data->env);
	else
		data->env = ft_export(data->env, args);
	return (data->env);
}

int	builtin_cmd_len(char *cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && cmd[len] != ' ')
		len++;
	return (len);
}
