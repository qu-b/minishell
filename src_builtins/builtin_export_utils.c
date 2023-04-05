/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:30:58 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/05 20:51:07 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**env_quote(char **env, char **envtmp)
{
	int	i;
	int	j;
	int	eq;

	i = -1;
	while (env[++i] != NULL)
	{
		envtmp[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 3));
		eq = ft_strchr_idx(env[i], '=');
		j = -1;
		while (++j <= eq)
			envtmp[i][j] = env[i][j];
		envtmp[i][eq + 1] = '\'';
		while (env[i][eq++])
			envtmp[i][++j] = env[i][eq];
		envtmp[i][j] = '\'';
		envtmp[i][++j] = 0x00;
	}
	envtmp[i] = NULL;
	return (envtmp);
}

char	**env_sort(char **env, char **envtmp)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (env[++i] != NULL)
	{
		j = -1;
		while (env[++j] != NULL)
		{
			if (envtmp[i][0] < envtmp[j][0])
			{
				tmp = envtmp[j];
				envtmp[j] = envtmp[i];
				envtmp[i] = tmp;
			}
		}
	}
	return (envtmp);
}

void	ft_export_export(char **env)
{
	char	**envtmp;

	envtmp = malloc(sizeof(char *) * (ft_argcount(env) + 1));
	envtmp = env_quote(env, envtmp);
	envtmp = env_sort(env, envtmp);
	ft_env(envtmp);
	ft_freeptr(envtmp);
}
