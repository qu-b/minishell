/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/30 16:32:34 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	minishell(void)
{
	char	*input;
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->env = getenv();
	input = "";
	while (input != NULL)
	{
		input = readline("minishell: ");
		add_history(input);
		if (parser(&data, input))
			return (1);
		else if (executor(data->tokens, getenv(data->env)))
			return (1);
		free(input);
	}
	return (0);
}
