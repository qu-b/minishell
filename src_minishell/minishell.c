/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/03 10:15:11 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	minishell(char **envp)
{
	char	*input;
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->env = envp;
	input = "";
	while (input != NULL)
	{
		input = readline("minishell: ");
		add_history(input);
		if (parser(&data, input))
			return (1);
		else if (executor(data, data->tokens))
			return (1);
		free(input);
	}
	return (0);
}