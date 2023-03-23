/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:01:20 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/23 11:01:01 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_export
{
	char	**new_env;
	int		argnb;
	int		envnb;
	int		envi;
	int		argi;
	int		valid_vars;
	int		env_max;
}	t_export;

# include <sys/types.h>
# include <dirent.h>

// builtins main ./minishell [command] [arg1] [arg2] ...
int		test_builtins(int argc, char **argv, char **envp);

int		ft_argcount(char **args);
void	ft_freeptr(char **s);

// echo is supposed to take arg like og, so f.ex:
// args[0] = "echo"
// args[1] = "-nnnn"
// args[2] = "blabla"
// etc
// arg[argnb] = NULL
void	ft_echo(char **args);
int		ft_echo_find_opt(char **args, int argnb);

// there might be something to change or add manually in env vars based on cd or other
// there might be a possible error to manage
// args is **envp from main
void	ft_env(char **env);

// there might be a possible error to manage
// args is **envp from main
void	ft_pwd(char **env);

// need to replace all possible vars before appending to env
char	**ft_export(char **env, char **args);
int		ft_export_init(t_export *exp, char **env, char **args);
void	ft_replace_env(char **args, char ***new_env, int replace);
char	**ft_add_env(char **env, char **args, char **new_env, int replace);
void	ft_replace_env_vars(t_export *exp, char **env, char **args);
int		ft_count_env_vars(t_export *exp, char **env, char **args);

// ??
void	ft_cd(char **args);

void	test_ft_echo(int argc, char **argv);
void	test_ft_cd(int argc, char **argv);
char	**ft_ptrdup(char **s, int n);
char	**ft_ptrdup_free(char **s, int n);
int		ft_strchr_idx(const char *s, int c);

#endif