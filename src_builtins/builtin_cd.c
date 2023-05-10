/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:32:10 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/10 13:19:24 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// change dir if valid, returns full dir path
char	*ft_cd_change(char *path)
{
	char	*full_path;

	full_path = NULL;
	if (access(path, F_OK) < 0)
	{
		write(2, "minishell: cd : invalid path\n", 29);
		g_data->exit_status = 1;
		return (NULL);
	}
	if (access(path, R_OK) < 0)
	{
		write(2, "minishell: cd : can't read file\n", 32);
		g_data->exit_status = 1;
		return (NULL);
	}
	if (chdir(path) < 0)
	{
		write(2, "minishell: cd : can't change dir\n", 33);
		g_data->exit_status = 1;
		return (NULL);
	}
	full_path = getcwd(full_path, 0);
	return (full_path);
}

char	*ft_cd_get_new_dir(char **args, char **env)
{
	char	*new_dir;

	new_dir = NULL;
	if (!args[1])
		new_dir = ft_getenv(env, "HOME");
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		new_dir = ft_getenv(env, "OLDPWD");
		if (new_dir != NULL)
			printf("%s\n", new_dir);
	}
	else if (args[1][0] != 0x00)
		new_dir = ft_strdup(args[1]);
	return (new_dir);
}

// updates PWD and OLDPWD in env
int	ft_cd_update_env(t_export *cd, char **env, char **args)
{
	char	*cwd;
	char	*full_path;
	char	*new_dir;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	new_dir = NULL;
	new_dir = ft_cd_get_new_dir(args, env);
	full_path = ft_cd_change(new_dir);
	if (full_path == NULL)
	{
		if (new_dir != NULL)
			free(new_dir);
		free(cwd);
		return (-1);
	}
	cd->new_env = ft_export_string(env, "PWD=", full_path);
	cd->new_env = ft_export_string(cd->new_env, "OLDPWD=", cwd);
	free(full_path);
	if (new_dir != NULL)
		free(new_dir);
	free(cwd);
	return (0);
}

char	**ft_cd(char **env, char **args)
{
	t_export		*cd;
	char			**new_env;

	if (!args || !*args || !env || !*env)
		return (env);
	cd = malloc(sizeof(cd));
	if (!cd)
		return (env);
	if (ft_cd_update_env(cd, env, args) < 0)
	{
		free(cd);
		return (env);
	}
	new_env = ft_ptrdup_free(cd->new_env, ft_argcount(cd->new_env));
	free(cd);
	if (new_env == NULL)
		return (env);
	g_data->exit_status = 0;
	return (new_env);
}
