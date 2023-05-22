/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:30:15 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/10 19:25:05 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// frees and exits the minishell
int	exec_exit(void)
{
	free_cmd(&g_data->cmd);
	free(g_data->pid);
	free_data();
	exit(0);
}

// executes the export builtin
char	**exec_export(char **args)
{
	if (args[1] == NULL)
		ft_export_export(g_data->env);
	else
		g_data->env = ft_export(g_data->env, args);
	return (g_data->env);
}

// finds the lenght of *cmd until first space or end of string
int	builtin_cmd_len(char *cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && cmd[len] != ' ')
		len++;
	return (len);
}
