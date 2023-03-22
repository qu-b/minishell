/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:01:20 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/22 23:47:42 by kpawlows         ###   ########.fr       */
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

// echo is supposed to take arg like og, so :
// arg[0] = "echo"
// arg[1] = "-nnnn"
// arg[2] = "blabla"
// etc
// arg[argnb] = NULL
void	ft_echo(char **args);
int		ft_echo_find_opt(char **args, int argnb);

// there might be something to change or add manually in env vars based on cd or other
// there might be a possible error to manage
// args is **envp from main
void	ft_env(char **args);

// there might be a possible error to manage
// args is **envp from main
void	ft_pwd(char **args);

// ??
void	ft_cd(char **args);

void	test_ft_echo(int argc, char **argv);
void	test_ft_cd(int argc, char **argv);

#endif