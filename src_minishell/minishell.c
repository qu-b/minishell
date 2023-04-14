/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/13 16:49:09 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	minishell(char **envp)
{
	char	*input;

	(void) envp;
	input = "";
	sig_acccept();
	while (input != NULL)
	{
		input = readline("minishell: ");
		if (!input)
		{
			free(input);
			// for ctrl-d, use builtin exit, at least its free() part
			break ;
		}
		add_history(input);
		if (parser(input))
			return (1);
		else if (executor(&g_data->tokens))
			return (1);
		free(input);
	}
	show_ctrl_enable();
	return (0);
}
