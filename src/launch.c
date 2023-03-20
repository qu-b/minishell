/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/21 00:16:22 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
# include "../lib/inc/libft.h"

int	check_builtin(char *input)
{
	char **split;

	split = ft_split(input, ' ');

	char *new_prog = "/bin/pwd";
	if (!ft_strncmp(&input[0], "pwd", 3))
	{
		execve(new_prog, split, NULL);
	}
	return (1);
}

// int	parse_input(char *input)
// {
// 	int	i;

// 	i = 0;
// 	if (check_builtin(input))
// 	{
// 		while (input[i])
// 		{
// 		}
// 	}
// 	return (1);
// }

void	launch_msh(void)
{
	char	*input;

	while ((input = readline("minishell: ")) != NULL)
	{
		check_builtin(input);
		add_history(input);
		// parse_input(input);
		printf("%s\n", input);
	}
}
