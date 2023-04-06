/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/06 07:05:35 by kpawlows         ###   ########.fr       */
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
		else if (executor(g_data->tokens))
			return (1);
		free(input);
	}
	return (0);
}
