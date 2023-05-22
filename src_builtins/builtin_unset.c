/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 05:12:37 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/22 12:34:55 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// checks whether args exist in old env
// if so, skips their copy from the old env to the new env
int	remove_env(t_export *exp, char **env, char **args)
{
	int	eq;
	int	envi;
	int	argi;
	int	removed;

	envi = -1;
	while (++envi < exp->envnb)
	{
		argi = -1;
		removed = 0;
		eq = ft_strchr_idx(env[envi], '=');
		while (++argi < exp->argnb && eq > -1)
		{
			if (ft_strncmp(env[envi], args[argi], eq) == 0)
				removed = 1;
		}
		if (removed == 0)
		{
			exp->new_env[exp->env_max] = ft_strdup(env[envi]);
			if (!exp->new_env[exp->env_max])
				return (-1);
			exp->env_max++;
		}
	}
	return (0);
}

// inits t_export struct for ft_unset
int	unset_init(t_export *exp, char **env, char **args)
{
	exp->argnb = ft_argcount(args);
	exp->envnb = ft_argcount(env);
	exp->env_max = 0;
	exp->new_env = malloc(sizeof(char *) * (exp->envnb + 1));
	if (!exp->new_env)
		return (-1);
	return (0);
}

// unsets the env variables passed as arguments, returns the new env
// returns the old env if an error occurs
char	**ft_unset(char **env, char **args)
{
	char		**new_env;
	t_export	*exp;

	args++;
	exp = malloc(sizeof(t_export));
	if (!exp)
		return (env);
	if (unset_init(exp, env, args) < 0)
	{
		free(exp);
		return (env);
	}
	if (remove_env(exp, env, args) < 0)
	{
		ft_freeptr(exp->new_env);
		free(exp);
		return (env);
	}
	exp->new_env[exp->env_max] = NULL;
	new_env = ft_ptrdup_free(exp->new_env, exp->env_max);
	free(exp);
	if (!new_env)
		return (env);
	ft_freeptr(env);
	return (new_env);
}
