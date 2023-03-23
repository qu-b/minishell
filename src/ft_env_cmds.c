/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:17:58 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/23 05:13:15 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		ft_printf("%s\n", env[i]);
	return ;
}

void	ft_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			ft_printf("%s\n", &env[i][4]);
			break ;
		}
		i++;
	}
}
