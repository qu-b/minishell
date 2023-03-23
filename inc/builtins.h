/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:01:20 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/23 05:18:42 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// # include "../lib/inc/libft.h" // change this to "../lib/inc/libft.h", remove rest
// # include <stdio.h>
// # include <stdlib.h>
// # include <string.h>
// # include <ctype.h>
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

// ugly but works, would be better to use a struct
// works only with one env variable check og
char	**ft_export(char **env, char **args, int envnb);
void	ft_replace_env(char **args, char ***new_env, int replace);
char	**ft_add_env(char **env, char **args, char **new_env, int replace);
int		ft_find_env_var(char **env, char **args);

// ??
void	ft_cd(char **args);

void	test_ft_echo(int argc, char **argv);
void	test_ft_cd(int argc, char **argv);
char	**ft_ptrdup(char **s, int n);
char	**ft_ptrdup_free(char **s, int n);
int		ft_strchr_idx(const char *s, int c);

#endif