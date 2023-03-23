/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 05:12:37 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/23 11:00:34 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// export PATH="$PATH:/Applications/Visual Studio Code.app/Contents/Resources/app/bin"

int	ft_copy_vars(t_export *exp, char **env, char **args)
{
	int	idx;
	
	idx = ft_strchr_idx(args[exp->argi], '=');
	if (idx > 0 && ft_strncmp(env[exp->envi], args[exp->argi], idx) == 0)
	{
		exp->new_env[exp->envi] = ft_strdup(args[exp->argi]);
		exp->valid_vars--;
		exp->argi++;
	}
	else
		exp->new_env[exp->envi] = ft_strdup(env[exp->envi]);
	return (0);
}

void	ft_process_vars(t_export *exp, char **env, char **args)
{
	while (exp->envi < exp->envnb)
	{
		ft_copy_vars(exp, env, args);
		exp->envi++;
	}
	while (args[exp->argi] && exp->valid_vars > 0)
	{
		exp->new_env[exp->envi] = ft_strdup(args[exp->argi]);
		exp->envi++;
		exp->argi++;
		exp->env_max++;
		exp->valid_vars--;
		// ft_printf("envi = %d\nargi = %d", exp->envi, exp->argi);
	}
	// ft_printf("new env [%d]= %s\n", exp->envi - 1, exp->new_env[exp->envi - 1]);
	exp->valid_vars--;
	exp->envi++;
	ft_printf("argnb = %d\nenvnb = %d\nvalid_vars = %d\nmalloc = %d\nenv_max = %d\nNULL = %d\n", exp->argnb, exp->envnb, exp->valid_vars, exp->envnb + exp->argnb, exp->env_max, exp->env_max);
}

int	ft_count_env_vars(t_export *exp, char **env, char **args)
{
	int	idx;
	int	arg_idx;

	(void) env;
	arg_idx = -1;
	while (++arg_idx < exp->argnb)
	{
		idx = -1;
		idx = ft_strchr_idx(args[arg_idx], '=');
		if (idx < 0)
			return (-1);
		exp->valid_vars++;
	}
	return (-1);
}

int	ft_export_init(t_export *exp, char **env, char **args)
{
	exp->valid_vars = 0;
	exp->argi = 0;
	exp->envi = 0;
	exp->argnb = ft_argcount(args);
	exp->envnb = ft_argcount(env);
	ft_count_env_vars(exp, env, args);
	exp->env_max = exp->envnb;
	// if (ft_argcount(args) < 3)
	// 	return (-1);
	exp->new_env = malloc(sizeof(char *) * (exp->envnb + exp->argnb + 1000));
	return (0);
}

char	**ft_export(char **env, char **args)
{
	char		**new_env;
	t_export	*exp;

	args++;
	exp = malloc(sizeof(t_export));
	ft_export_init(exp, env, args);
	ft_process_vars(exp, env, args);
	exp->new_env[exp->env_max] = NULL;

	new_env = ft_ptrdup_free(exp->new_env, exp->env_max);
	free(exp);
	return (new_env);
}