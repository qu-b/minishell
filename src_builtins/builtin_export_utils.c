/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:30:58 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/06 05:41:33 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**env_quote(char **env, char **envtmp, int i, int j)
{
	int	k;
	int	eq;

	while (env[++i] != NULL)
	{
		envtmp[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 14));
		if (!envtmp[i])
			return (NULL);
		eq = ft_strchr_idx(env[i], '=');
		k = ft_strlcpy(envtmp[i], "declare -x ", 12);
		j = -1;
		while (++j <= eq)
			envtmp[i][k++] = env[i][j];
		envtmp[i][k] = '"';
		while (env[i][eq++])
			envtmp[i][++k] = env[i][eq];
		envtmp[i][k] = '"';
		envtmp[i][++k] = 0x00;
	}
	envtmp[i] = NULL;
	return (envtmp);
}

char	**env_sort(char **envtmp)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (envtmp[++i] != NULL)
	{
		j = -1;
		while (envtmp[++j] != NULL)
		{
			if (envtmp[i][11] < envtmp[j][11])
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
	envtmp = env_quote(env, envtmp, -1, -1);
	envtmp = env_sort(envtmp);
	ft_env(envtmp);
	ft_freeptr(envtmp);
}

int	ft_argcount(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}
