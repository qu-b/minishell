/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:01:20 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/06 05:53:31 by kpawlows         ###   ########.fr       */
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

int		exec_builtins(t_data *data, char *args);
int		exec_exit(t_data *data, char **args, char *cmd);
char	**exec_export(t_data *data, char **args);

// return lenght until space or end of string
int		builtin_cmd_len(char *cmd);

// builtins main ./minishell [command] [arg1] [arg2] ...
int		test_builtins(int argc, char **argv, char **envp);

// prints args[1] to args[n] with spaces between
void	ft_echo(char **args);
int		echo_find_opt(char **args, int argnb);
int		find_hyphen(char **args, int argnb);

// prints env
void	ft_env(char **env);
void	ft_pwd(char **env);

// returns a malloced string with env var value matching var
char	*ft_getenv(char **env, char *var);

// returns a malloced env with exported vars of NAME and VALUE, frees env
char	**ft_export_string(char **env, char *name, char *value);

// returns a malloced copy of env with exported vars, frees old env
// returns og env if fail
// shows declared env vars if no args
char	**ft_export(char **env, char **args);
int		export_init(t_export *exp, char **env, char **args);
int		append_env(t_export *exp, char **env, char **args);
int		replace_env(t_export *exp, char **env, char **args);

// replicates the behaviour of export with no args
void	ft_export_export(char **env);
char	**env_sort(char **envtmp);
char	**env_quote(char **env, char **envtmp, int i, int j);

// returns a malloced copy of env with unset vars, frees old env
// returns og env if fail
char	**ft_unset(char **env, char **args);
int		unset_init(t_export *exp, char **env, char **args);
int		remove_env(t_export *exp, char **env, char **args);

// inits minishell env variable, dups envp, unsets "_"
char	**init_env(t_data *data, char **envp);

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
void	ft_printptr(char **s);

#endif
