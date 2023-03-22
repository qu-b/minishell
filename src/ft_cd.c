/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:32:10 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/22 23:24:44 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

void	ft_cd(char **args)
{
	DIR *dir;
	(void) args;
	// ft_printf("%s\n", args[1]);
	dir = opendir(args[1]);
	if (!dir)
		return ;
	readdir(dir);
	// ??
	return ;
}

void	test_ft_cd(int argc, char **argv)
{
	char	**args;
	int		i;

	i = 1;
	args = malloc(sizeof(char *) * (argc + 2));
	args[0] = ft_strdup("cd");
	// while (++i < argc)
		args[i] = ft_strdup(argv[i]);
	ft_cd(args);
}
