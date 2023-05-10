/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:17:02 by fcullen           #+#    #+#             */
/*   Updated: 2023/05/10 11:20:55 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Global pointer to the t_data struct - added definition to minishell.h
t_data	*g_data = NULL;

// Define the get_data function to create and return the singleton instance
t_data	*get_data(char **envp)
{
	if (!g_data)
	{
		g_data = malloc(sizeof(t_data));
		if (!g_data)
			return (NULL);
		init_env(envp);
		g_data->tokens = NULL;
		g_data->ext = 0;
		g_data->exit_status = 0;
		g_data->input = "";
	}
	return (g_data);
}

void	free_data(void)
{
	free_tokens(&g_data->tokens);
	free_cmd(&g_data->cmd);
	free(g_data->input);
	ft_freeptr(g_data->env);
	free(g_data);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	g_data = get_data(envp);
	minishell();
	free_data();
	show_ctrl_enable();
	return (0);
}
