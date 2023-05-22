/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:17:58 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/22 13:55:45 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// prints the environment variables, separates them by newlines
void	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		printf("%s\n", env[i]);
	return ;
}

// finds and prints the current working directory
void	ft_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		g_data->exit_status = 0;
	}
	else
	{
		write(2, "pwd: error!\n", 12);
		g_data->exit_status = 1;
	}
}

// returns a malloced string with the value of var in **env
// returns NULL if none found
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
			return (ft_strdup(&env[i][eq + 1]));
		}
	}
	ft_freeptr(args);
	return (NULL);
}

// 
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

// inits minishell env variable, dups envp, unsets "_"
// augments and exports "SHLVL", changes "SHELL"
char	**init_env(char **envp)
{
	char	**tmp;
	int		shlvl;
	char	*shlvl_itoa;

	g_data->env = ft_ptrdup(envp, ft_argcount(envp));
	tmp = malloc(sizeof(char *) * 3);
	tmp[0] = ft_strdup("unset");
	tmp[1] = ft_strdup("_");
	tmp[2] = NULL;
	g_data->env = ft_unset(g_data->env, tmp);
	ft_freeptr(tmp);
	shlvl = 0;
	shlvl = ft_atoi(getenv("SHLVL"));
	shlvl++;
	shlvl_itoa = ft_itoa(shlvl);
	g_data->env = ft_export_string(g_data->env, "SHLVL=", shlvl_itoa);
	free(shlvl_itoa);
	g_data->env = ft_export_string(g_data->env, "SHELL=", "minishell");
	return (g_data->env);
}
