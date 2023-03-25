/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 05:12:37 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/24 17:05:58 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// check if valid args exist in the old env
// if so, replace them in the new env and mark replaced args for append
int	ft_replace_env(t_export *exp, char **env, char **args)
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
			if (eq < 0)
				return (0);
			if (ft_strncmp(env[envi], args[argi], eq) == 0)
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
	int	appi;
	int	argi;
	
	argi = -1;
	appi = exp->envnb;
	while (++argi < exp->argnb)
	{
		envi = -1;
		eq = ft_strchr_idx(args[argi], '=');
		while (++envi < exp->envnb)
		{
			if (eq < 0)
				return (0);
			if (ft_strncmp(env[envi], args[argi], eq) != 0)
			{
				exp->new_env[appi] = ft_strdup(args[argi]);
				if (exp->new_env[appi] == NULL)
					return (-1);
				appi++;
				exp->env_max++;
				break ;
			}
		}
	}
	return (0);
}

int	ft_export_init(t_export *exp, char **env, char **args)
{
	char	**new_env;
	int		i;

	exp->argnb = ft_argcount(args);
	exp->envnb = ft_argcount(env);
	exp->env_max = exp->envnb;
	new_env = malloc(sizeof(char *) * (exp->envnb + exp->argnb + 1));
	if (!new_env)
		return (-1);
	i = -1;
	while (++i < exp->envnb)
		new_env[i] = ft_strdup(env[i]);
	new_env[i] = NULL;
	exp->new_env = new_env;
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
		free(exp);
		return (env);
	}
	if (ft_replace_env(exp, env, args) < 0 || ft_append_env(exp, env, args) < 0)
	{
		exp->new_env[exp->env_max] = NULL;
		ft_freeptr(exp->new_env);
		free(exp);
		return (env);
	}
	exp->new_env[exp->env_max] = NULL;
	// ft_printf("envnb = %d\nargnb = %d\nenv_max (NULL) == %d\n", exp->envnb, exp->argnb, exp->env_max);
	new_env = ft_ptrdup_free(exp->new_env, exp->env_max);
	free(exp);
	if (!new_env)
		return (env);
	return (new_env);
}