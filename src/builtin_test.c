/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:30:15 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/25 03:20:36 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	test_builtins(int argc, char **argv, char **envp)
{
	char	**env_mod;
	int		envnb;

	if (argc < 2)
		return (0);

	envnb = ft_argcount(envp);
	env_mod = ft_ptrdup(envp, envnb);

	if (ft_strncmp(argv[1], "echo", 4) == 0)
		ft_echo(++argv);
	else if (ft_strncmp(argv[1], "env", 3) == 0)
		ft_env(env_mod);
	else if (ft_strncmp(argv[1], "pwd", 3) == 0)
		ft_pwd(env_mod);
	else if (ft_strncmp(argv[1], "cd", 2) == 0)
	{
		env_mod = ft_cd(env_mod, ++argv);
		ft_env(env_mod);
	}
	else if (ft_strncmp(argv[1], "export", 6) == 0)
	{
		env_mod = ft_export(env_mod, ++argv);
		ft_env(env_mod);
	}
	else if (ft_strncmp(argv[1], "unset", 5) == 0)
	{
		env_mod = ft_unset(env_mod, ++argv);
		ft_env(env_mod);
	}
	ft_freeptr(env_mod);
	return (0);
}