/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 09:12:28 by zaphod           #+#    #+#             */
/*   Updated: 2023/05/08 14:39:46 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free command
void	free_cmd(t_cmd *cmd)
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
	cmd = NULL;
}

void	del_token(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	if ((*tokens)->next)
		(*tokens) = (*tokens)->next;
	if (tmp)
	{
		if (tmp->value)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	free_tokens(t_token **head)
{
	t_token	*temp;

	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		del_token(&temp);
	}
	free(*head);
	*head = NULL;
}
