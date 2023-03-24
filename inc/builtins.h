/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:01:20 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/24 20:52:33 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_export
{
	char	**new_env;
	int		argnb;
	int		envnb;
	int		env_max;
}	t_export;

# include <sys/types.h>
# include <dirent.h>

// builtins main ./minishell [command] [arg1] [arg2] ...
int		test_builtins(int argc, char **argv, char **envp);

// echo is supposed to take arg like og, so f.ex:
// args[0] = "echo"
// args[1] = "-nnnn"
// args[2] = "blabla"
// etc
// arg[argnb] = NULL
void	ft_echo(char **args);
int		ft_echo_find_opt(char **args, int argnb);

// env is **envp from main
void	ft_env(char **env);

// env is **envp from main
void	ft_pwd(char **env);

// env is **envp from main
// args are variable names, should work like the original
// returns a copy of env with valid vars replaced or appended
// (there might be something to change or add manually in env vars based on cd or other)
int		ft_replace_env(t_export *exp, char **env, char **args);
int		ft_append_env(t_export *exp, char **env, char **args);
int		ft_export_init(t_export *exp, char **env, char **args);
char	**ft_export(char **env, char **args);

int		ft_remove_env(t_export *exp, char **env, char **args);
int		ft_unset_init(t_export *exp, char **env, char **args);
char	**ft_unset(char **env, char **args);

// ??
void	ft_cd(char **args);

void	ft_freeptr(char **s);
int		ft_argcount(char **args);
char	**ft_ptrdup(char **s, int n);
char	**ft_ptrdup_free(char **s, int n);
int		ft_strchr_idx(const char *s, int c);

#endif