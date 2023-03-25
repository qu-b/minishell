/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:01:20 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/25 15:06:06 by kpawlows         ###   ########.fr       */
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

void	ft_env(char **env);
void	ft_pwd(char **env);

// returns a malloced string with env var value matching var
char	*ft_get_env_var(char **env, char *var);
// returns a malloced env with exported vars of NAME and VALUE, frees env
char	**ft_export_string(char **env, char *name, char *value);

// returns a malloced copy of env, frees old env
// returns og env if fail
// maybe env should be in a struct
char	**ft_export(char **env, char **args);
int		ft_export_init(t_export *exp, char **env, char **args);
int		ft_append_env(t_export *exp, char **env, char **args);
int		ft_replace_env(t_export *exp, char **env, char **args);

// same as export
char	**ft_unset(char **env, char **args);
int		ft_unset_init(t_export *exp, char **env, char **args);
int		ft_remove_env(t_export *exp, char **env, char **args);

// same as export
// updates PWD and OLDPWD in env
// changes dir for the current process, see with pipes
char	**ft_cd(char **env, char **args);
int		ft_cd_update_env(t_export *cd, char **env, char **args);
char	*ft_cd_change(char *path);


void	ft_freeptr(char **s);
int		ft_argcount(char **args);
char	**ft_ptrdup(char **s, int n);
char	**ft_ptrdup_free(char **s, int n);
int		ft_strchr_idx(const char *s, int c);

#endif