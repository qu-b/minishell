/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/28 16:36:48 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	launch_msh(void)
{
	char	*input;
	// t_token	*tokens;

	input = "";
	while (input != NULL)
	{
		input = readline("minishell: ");
		input[ft_strlen(input)] = '\0';
		add_history(input);
		if (parser(input))
			return (1);
	}
	return (0);
}
