/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:01:20 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/22 12:48:25 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <sys/types.h>
# include <dirent.h>

typedef struct s_export
{
	char	**new_env;
	int		argnb;
	int		envnb;
	int		env_max;
}	t_export;

int		exec_exit(void);
char	**exec_export(char **args);

int		builtin_cmd_len(char *cmd);

void	ft_echo(char **args);
int		echo_find_opt(char **args, int argnb);

void	ft_env(char **env);
void	ft_pwd(void);

char	**ft_export(char **env, char **args);
int		export_init(t_export *exp, char **env, char **args);
int		append_env(t_export *exp, char **env, char **args);
int		replace_env(t_export *exp, char **env, char **args);
int		compare_vars(char **env, char **args, int argi, int envi);
int		check_varname(char **args, int argi, int eqa);

void	ft_export_export(char **env);
char	**env_sort(char **envtmp);
char	**env_quote(char **env, char **envtmp, int i, int j);

char	**ft_unset(char **env, char **args);
int		unset_init(t_export *exp, char **env, char **args);
int		remove_env(t_export *exp, char **env, char **args);

char	**init_env(char **envp);

// same as export
// updates PWD and OLDPWD in env
// changes dir for the current process, see with pipes
char	**ft_cd(char **env, char **args);
int		ft_cd_update_env(t_export *cd, char **env, char **args);
char	*ft_cd_get_new_dir(char **args, char **env);
char	*ft_cd_change(char *path);

// returns a malloced string with env var value matching var
char	*ft_getenv(char **env, char *var);

// returns a malloced env with exported vars of NAME and VALUE, frees env
char	**ft_export_string(char **env, char *name, char *value);

int		ft_argcount(char **args);
char	**ft_ptrdup(char **s, int n);
char	**ft_ptrdup_free(char **s, int n);
int		ft_strchr_idx(const char *s, int c);
void	ft_printptr(char **s);

#endif
