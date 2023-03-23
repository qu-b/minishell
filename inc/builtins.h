/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:01:20 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/23 02:47:50 by kpawlows         ###   ########.fr       */
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

// export just adds strings to **env_mod, need to manage existing env vars etc
// depends on input, ex if args will first be expanded from $PATH to the actual PATH value
// wonky to export without the "$PATH" keyword somewher in args though
char	**ft_export(char **env, char **args, int envnb);

// ??
void	ft_cd(char **args);

void	test_ft_echo(int argc, char **argv);
void	test_ft_cd(int argc, char **argv);
char	**ft_ptrdup(char **s, int n);
char	**ft_ptrdup_free(char **s, int n);

#endif