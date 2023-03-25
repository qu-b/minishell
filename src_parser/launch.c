/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:21 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/25 15:10:13 by fcullen          ###   ########.fr       */
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

void	launch_msh(void)
{
	char	*input;
	t_token	*tokens;

	input = "";
	while (input != NULL)
	{
		input = readline("minishell: ");
		input[ft_strlen(input)] = '\0';
		// printf("%s\n", input);
		add_history(input);
		check_builtin(input);
		tokens = lexer(input);
		int i = -1;
		while (tokens[++i].value)
			printf("%s : %d\n", tokens[i].value, tokens[i].type);
		// parse_input(input);
		// printf("%s\n", input);
	}
}
