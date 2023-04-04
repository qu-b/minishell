/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 05:12:37 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/04 08:14:38 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// compare 2 variable names
// return -1 if either is non valid
// retur 0 if both are valid but different
// return varlen if both are the same
int	ft_compare_vars(char **env, char **args, int argi, int envi)
{
	int	eqa;
	int	eqe;

	if (argi == -1)
		argi++;
	if (envi == -1)
		envi++;
	eqa = ft_strchr_idx(args[argi], '=');
	eqe = ft_strchr_idx(env[envi], '=');
	if (eqa < 0 || eqe < 0)
		return (-1);
	if (eqe == eqa && ft_strncmp(args[argi], env[envi], eqa) == 0)
		return (eqa);
	return (0);
}

// check if valid args exist in the old env
// if so, replace them in the new env and mark replaced args for append
int	ft_replace_env(t_export *exp, char **env, char **args)
{
	int	envi;
	int	argi;
	
	argi = -1;
	while (++argi < exp->argnb)
	{
		envi = -1;
		if (ft_compare_vars(env, args, argi, envi) < 0)
			return (0);
		while (++envi < exp->envnb)
		{
			if (ft_compare_vars(env, args, argi, envi) == 0)
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

// check if valid args don't exist in the old env
// if so, append them to the new env
int	ft_append_env(t_export *exp, char **env, char **args)
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
			if (eq == -2)
				break ;
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

int	ft_export_init(t_export *exp, char **env, char **args)
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

char	**ft_export(char **env, char **args)
{
	char		**new_env;
	t_export	*exp;

	args++;
	exp = malloc(sizeof(t_export));
	if (ft_export_init(exp, env, args) < 0)
	{
		ft_freeptr(exp->new_env);
		free(exp);
		return (env);
	}
	if (ft_replace_env(exp, env, args) < 0 || ft_append_env(exp, env, args) < 0)
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