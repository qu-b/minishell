/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:12:28 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/18 10:56:20 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free command
void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		// printf("cleanup {%s}\n", cmd->name);
		if (cmd->name)
		{
			free(cmd->name);
			cmd->name = NULL;
		}
		if (cmd->args)
		{
			double_free(cmd->args);
			cmd->args = NULL;
		}
		// printf("cleanup {%s}\n", cmd->name);
	}
	cmd = NULL;
}