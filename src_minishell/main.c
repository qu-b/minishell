/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:17:02 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/06 05:41:45 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Global pointer to the t_data struct
t_data *g_data = NULL;

// Define the get_data function to create and return the singleton instance
t_data *get_data()
{
	if (!g_data)
	{
		g_data = malloc(sizeof(t_data));
		if (!g_data)
			return (NULL);
		// Initialize g_data here
	}
	return g_data;
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	minishell(envp); // Should take a copy of envp
	// terminate_msh();
	// test_builtins(argc, argv, envp);
	return (0);
}
