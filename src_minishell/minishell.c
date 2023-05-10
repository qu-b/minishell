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

#include "minishell.h"

int	minishell(void)
{
	char	*ps1;

	sig_acccept();
	while (g_data->input != NULL)
	{
		ps1 = prompt();
		if (ps1 == NULL)
			ps1 = ft_strdup("\033[1;32mminishell : :\033[0m");
		g_data->input = readline(ps1);
		free(ps1);
		if (!g_data->input)
			break ;
		add_history(g_data->input);
		if (parser(g_data->input))
			write(2, "Command Error\n", 14);
		else if (executor())
			return (1);
		free_tokens(&g_data->tokens);
		free(g_data->input);
	}
	return (0);
}
