/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:30:15 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/22 23:45:19 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	test_builtins(int argc, char **argv, char **envp)
{
	if (argc < 2)
		return (0);
	if (ft_strncmp(argv[1], "echo", 4) == 0)
		ft_echo(++argv);
	if (ft_strncmp(argv[1], "env", 4) == 0)
		ft_env(envp);
	if (ft_strncmp(argv[1], "pwd", 4) == 0)
		ft_pwd(envp);
	// test_ft_cd(argc, argv);
	return (0);
}