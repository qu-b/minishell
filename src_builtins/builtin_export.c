/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 05:12:37 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/22 12:44:55 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// compares 2 variable names
// returns -1 if either is non valid
// returns 0 if both are valid but different
// returns varlen if both are the same
int	compare_vars(char **env, char **args, int argi, int envi)
{
	int	eqa;
	int	eqe;

	if (argi == -1)
		argi++;
	if (envi == -1)
		envi++;
	eqa = ft_strchr_idx(args[argi], '=');
	eqe = ft_strchr_idx(env[envi], '=');
	if (check_varname(args, argi, eqa) < 0)
		return (-1);
	if (eqa < 0 || eqe < 0)
		return (-1);
	if (eqe == eqa && ft_strncmp(args[argi], env[envi], eqa) == 0)
		return (eqa);
	return (0);
}

// checks if valid args exist in the old env
// if so, replaces them in the new env and marks replaced args for append
int	replace_env(t_export *exp, char **env, char **args)
{
	int	envi;
	int	argi;

	argi = -1;
	while (++argi < exp->argnb)
	{
		envi = -1;
		if (compare_vars(env, args, argi, envi) < 0)
			return (0);
		while (++envi < exp->envnb)
		{
			if (compare_vars(env, args, argi, envi) == 0)
				(void) envi;
			else
			{
				free(exp->new_env[envi]);
				exp->new_env[envi] = ft_strdup(args[argi]);
				if (exp->new_env[envi] == NULL)
					return (-1);
				args[argi][0] = '=';
				break ;
			}
		}
	}
	return (0);
}

// checks if valid args don't exist in the old env
// if so, appends them to the new env
int	append_env(t_export *exp, char **env, char **args)
{
	int	eq;
	int	envi;
	int	argi;

	argi = -1;
	while (++argi < exp->argnb)
	{
		envi = -1;
		eq = ft_strchr_idx(args[argi], '=');
		while (++envi < exp->envnb)
		{
			if (eq == -1)
				return (0);
			if (ft_strncmp(env[envi], args[argi], eq) != 0)
			{
				exp->new_env[exp->env_max] = ft_strdup(args[argi]);
				if (exp->new_env[exp->env_max] == NULL)
					return (-1);
				exp->env_max++;
				break ;
			}
		}
	}
	return (0);
}

// inits the export struct for ft_export
int	export_init(t_export *exp, char **env, char **args)
{
	int	i;

	exp->argnb = ft_argcount(args);
	exp->envnb = ft_argcount(env);
	exp->env_max = exp->envnb;
	exp->new_env = malloc(sizeof(char *) * (exp->envnb + exp->argnb + 1));
	if (!exp->new_env)
		return (-1);
	i = -1;
	while (++i < exp->envnb)
	{
		exp->new_env[i] = ft_strdup(env[i]);
		if (!exp->new_env[i])
			return (-1);
	}
	exp->new_env[i] = NULL;
	return (0);
}

// exports the env variables passed as arguments, until one is invalid
// returns a new env, frees old env, returns env if fail
// shows declared env vars if no args
char	**ft_export(char **env, char **args)
{
	char		**new_env;
	t_export	*exp;

	args++;
	exp = malloc(sizeof(t_export));
	if (export_init(exp, env, args) < 0)
	{
		ft_freeptr(exp->new_env);
		free(exp);
		return (env);
	}
	if (replace_env(exp, env, args) < 0 || append_env(exp, env, args) < 0)
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
