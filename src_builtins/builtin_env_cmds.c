/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:17:58 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/06 07:00:46 by kpawlows         ###   ########.fr       */
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

char	*ft_getenv(char **env, char *var)
{
	int	eq;
	int	i;

	i = -1;
	while (env[++i])
	{
		eq = ft_strchr_idx(env[i], '=');
		if (eq > -1 && ft_strncmp(env[i], var, eq) == 0)
			return (&env[i][eq + 1]);
	}
	return (NULL);
}

char	**ft_export_string(char **env, char *name, char *value)
{
	char	**new_env;
	char	**tmp;

	tmp = malloc(sizeof(char *) * 3);
	tmp[0] = ft_strdup("export");
	tmp[1] = ft_strjoin(name, value);
	tmp[2] = NULL;
	new_env = ft_export(env, tmp);
	ft_freeptr(tmp);
	return (new_env);
}

char	**init_env(char **envp)
{
	char	**tmp;

	g_data->env = ft_ptrdup(envp, ft_argcount(envp));
	tmp = malloc(sizeof(char *) * 3);
	tmp[0] = ft_strdup("unset");
	tmp[1] = ft_strdup("_");
	tmp[2] = NULL;
	g_data->env = ft_unset(g_data->env, tmp);
	ft_freeptr(tmp);
	return (g_data->env);
}
