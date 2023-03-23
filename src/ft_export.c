/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 05:12:37 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/23 05:18:21 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// export PATH="$PATH:/Applications/Visual Studio Code.app/Contents/Resources/app/bin"
int	ft_find_env_var(char **env, char **args)
{
	int		i;
	int		arg_idx;
	int		env_idx;

	i = -1;
	arg_idx = -1;
	env_idx = -1;
	while (args[++i])
	{
		arg_idx = ft_strchr_idx(args[i], '=');
		if (arg_idx > 0)
			break ;
	}
	if (arg_idx < 0)
		return (0);
	while (env[++env_idx])
	{
		if (ft_strncmp(env[env_idx], args[i], arg_idx) == 0)
			return (env_idx);
	}
	return (0);
}

void	ft_replace_env(char **args, char ***new_env, int replace)
{
	int	i;
	int	arg_idx;

	i = -1;
	while (args[++i])
	{
		arg_idx = ft_strchr_idx(args[i], '=');
		if (arg_idx > 0)
			break ;
	}
	new_env[0][replace] = ft_strdup(args[i]);
}

char	**ft_add_env(char **env, char **args, char **new_env, int replace)
{
	int	i;
	int	newargs;
	int	stop;
	

	newargs = 2;
	i = -1;
	stop = -1;
	while (args[++stop])
	{
		if (ft_strchr_idx(args[stop], '=') > 0)
			break;
	}
	while (env[++i])
	{
		if (i == replace && replace > 0)
			i++;
		new_env[i] = ft_strdup(env[i]);
	}
	while (new_env[i] && args[newargs])
	{
		if (newargs == stop)
			newargs++;
		if (args[newargs] == 0x00)
			break ;
		new_env[i] = ft_strdup(args[newargs]);
		newargs++;
		i++;
	}
	return (new_env);
}

char	**ft_export(char **env, char **args, int envnb)
{
	int		replace;
	int		argnb;
	char	**new_env;

	argnb = ft_argcount(args);
	if (ft_argcount(args) < 3)
		return (NULL);
	replace = ft_find_env_var(env, args);
	// ft_printf("replace = %d\n", replace);
	// ft_printf("envnb = %d\n", envnb);
	// ft_printf("malloc = %d\n", envnb + argnb);
	new_env = malloc(sizeof(char *) * (envnb + argnb));
	if (!new_env)
		return (NULL);
	if (replace > 0)
	{
		envnb--;
		// printf("\n\n\n\noui oui oui g trouve c idx %d, val : %s\n\n\n\n", replace, env[replace]);
		ft_replace_env(args, &new_env, replace);
	}
	new_env[envnb + argnb - 2] = NULL;
	new_env = ft_add_env(env, args, new_env, replace);
	ft_freeptr(env);
	return (new_env);
}