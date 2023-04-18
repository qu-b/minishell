/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:17:58 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/18 22:17:30 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		printf("%s\n", env[i]);
	return ;
}

void	ft_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		printf("CWD not set!\n");
}

char	*ft_getenv(char **env, char *var)
{
	char	**args;
	int		eq;
	int		i;

	if (!var)
		return (NULL);
	args = malloc(sizeof(char *) * 2);
	args[0] = ft_strjoin(var, "=");
	args[1] = NULL;
	i = -1;
	while (env[++i])
	{
		eq = compare_vars(env, args, 0, i);
		if (eq < 0)
			break ;
		if (eq > 0)
		{
			ft_freeptr(args);
			return (&env[i][eq + 1]);
		}
	}
	ft_freeptr(args);
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
	g_data->env = ft_export_string(g_data->env, "SHELL=", "minishell");
	return (g_data->env);
}
