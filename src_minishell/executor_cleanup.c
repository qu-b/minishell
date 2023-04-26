/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:12:28 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/26 14:53:18 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free command
void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->name)
		{
			free(cmd->name);
			cmd->name = NULL;
		}
		if (cmd->args)
		{
			ft_freeptr(cmd->args);
			cmd->args = NULL;
		}
	}
	cmd = NULL;
}

void	free_tokens(t_token **tokens)
{
	while (tokens)
		del_token(tokens);
}