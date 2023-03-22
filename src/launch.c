/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/22 16:47:19 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_builtin(char *input)
{
	char	**split;
	char	*new_prog;

	new_prog = "/bin/pwd";
	split = ft_split(input, ' ');
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
	t_token	*token;

	input = "";
	while (input != NULL)
	{
		input = readline("minishell: ");
		check_builtin(input);
		token = tokenize(input);
		printf("%s\n", token[0].value);
		printf("%s\n", token[1].value);
		printf("%s\n", token[2].value);
		add_history(input);
		// parse_input(input);
		// printf("%s\n", input);
	}
}
