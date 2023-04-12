/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:17:02 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/12 17:58:07 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Global pointer to the t_data struct - added definition to minishell.h
t_data *g_data = NULL;

// Define the get_data function to create and return the singleton instance
t_data *get_data(char **envp)
{
	if (!g_data)
	{
		g_data = malloc(sizeof(t_data));
		if (!g_data)
			return (NULL);
		init_env(envp);
		g_data->tokens = NULL; 
		g_data->ext = 0;
	}
	return g_data;
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	g_data = get_data(envp);
	minishell(envp);
	// terminate_msh();
	return (0);
}
