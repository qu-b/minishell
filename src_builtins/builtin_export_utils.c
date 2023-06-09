/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:30:58 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/22 12:38:33 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// checks if a variable name is valid (alphanumeric)
// prints error and returns -1 if not valid
int	check_varname(char **args, int argi, int eqa)
{
	int	i;

	i = -1;
	while (++i < eqa)
	{
		if (ft_isalnum(args[argi][i]) == 0)
		{
			write(2, "minishell: export: ", 19);
			write(2, "'", 1);
			write(2, args[argi], ft_strlen(args[argi]));
			write(2, "'", 1);
			write(2, ": not a valid identifier\n", 25);
			g_data->exit_status = 1;
			return (-1);
		}
	}
	return (0);
}

// adds declare -x and quotes to env variables(..?)
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

// sorts quoted declare -x env variables by name
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

// mimics the functionality of export without arguments
void	ft_export_export(char **env)
{
	char	**envtmp;

	envtmp = malloc(sizeof(char *) * (ft_argcount(env) + 1));
	envtmp = env_quote(env, envtmp, -1, -1);
	envtmp = env_sort(envtmp);
	ft_env(envtmp);
	ft_freeptr(envtmp);
}

// counts the number of strings in **args
int	ft_argcount(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return (0);
	while (args[i] != NULL)
		i++;
	return (i);
}
