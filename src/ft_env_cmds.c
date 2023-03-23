/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:17:58 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/23 03:09:20 by kpawlows         ###   ########.fr       */
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

char	**ft_export(char **env, char **args, int envnb)
{
	int		i;
	int		argnb;
	int		newargs;
	char	**new_env;

	argnb = ft_argcount(args);
	if (argnb < 3)
		return (NULL);
	i = -1;
	new_env = malloc(sizeof(char *) * (envnb + argnb - 1));
	if (!new_env)
		return (NULL);
	new_env[envnb + argnb - 2] = NULL;
	while (++i < envnb)
		new_env[i] = ft_strdup(env[i]);
	newargs = 2;
	while (i < (envnb + argnb - 2))
	{
		new_env[i] = ft_strdup(args[newargs]);
		newargs++;
		i++;
	}
	new_env[i] = NULL;
	ft_freeptr(env);
	return (new_env);
	
}