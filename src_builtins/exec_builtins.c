/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:30:15 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/05 20:48:44 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtins(t_data *data, char *cmd)
{
	char	**args;
	int		len;
	
	args = ft_split(cmd, ' ');
	len = builtin_cmd_len(cmd);
	if (ft_strncmp(args[0], "echo", len) == 0)
		ft_echo(args);
	else if (ft_strncmp(args[0], "env", len) == 0)
		ft_env(data->env);
	else if (ft_strncmp(args[0], "pwd", len) == 0)
		ft_pwd(data->env);
	else if (ft_strncmp(args[0], "cd", len) == 0)
		data->env = ft_cd(data->env, args);
	else if (ft_strncmp(args[0], "export", len) == 0)
	{
		if (args[1] == NULL)
			ft_export_export(data->env);
		else
			data->env = ft_export(data->env, args);
	}
	else if (ft_strncmp(args[0], "unset", len) == 0)
		data->env = ft_unset(data->env, args);
	else if (ft_strncmp(args[0], "exit", len) == 0)
	{
		ft_freeptr(data->env);
		ft_freeptr(args);
		free(cmd);
		// free everything everywhere all at once
		exit(0);
	}
	return (0);
}

int	builtin_cmd_len(char *cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && cmd[len] != ' ')
		len++;
	return (len);
}

// int	test_builtins(int argc, char **args, char **envp)
// {
// 	char	**env_mod;
// 	int		envnb;

// 	if (argc < 2)
// 		return (0);

// 	envnb = ft_argcount(envp);
// 	env_mod = ft_ptrdup(envp, envnb);

// 	if (ft_strncmp(args[1], "echo", 4) == 0)
// 		ft_echo(++args);
// 	else if (ft_strncmp(args[1], "env", 3) == 0)
// 		ft_env(env_mod);
// 	else if (ft_strncmp(args[1], "pwd", 3) == 0)
// 		ft_pwd(env_mod);
// 	else if (ft_strncmp(args[1], "cd", 2) == 0)
// 	{
// 		env_mod = ft_cd(env_mod, ++args);
// 		ft_printf("PWD=%s\n", ft_get_env_var(env_mod, "PWD"));
// 		ft_printf("OLDPWD=%s\n", ft_get_env_var(env_mod, "OLDPWD"));
// 	}
// 	else if (ft_strncmp(args[1], "export", 6) == 0)
// 	{
// 		env_mod = ft_export(env_mod, ++args);
// 		ft_env(env_mod);
// 	}
// 	else if (ft_strncmp(args[1], "unset", 5) == 0)
// 	{
// 		env_mod = ft_unset(env_mod, ++args);
// 		ft_env(env_mod);
// 	}
// 	else if (ft_strncmp(args[1], "exit", 4) == 0)
// 	{
// 		ft_freeptr(env_mod);
// 		// free everything everywhere all at once
// 		exit(0);
// 	}
// 	ft_freeptr(env_mod);
// 	return (0);
// }
