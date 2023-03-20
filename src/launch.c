/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/20 17:29:26 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	launch_msh(void)
{
	char	*input;

	while ((input = readline("minishell: ")) != NULL)
	{
		add_history(input);
		// parse_input(input);
		printf("%s\n", input);
	}
}
