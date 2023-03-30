/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:50:23 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/30 15:57:30 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "minishell.h"

int openfile(char *filename, int mode);
char *find_path(char **envp);
char *get_cmd(char **paths, char *cmd);
void exec(char *cmd, char **envp);
void redirect(char *cmd, char **env, int fdin);
int exec_pipe(int ac, char **av, char **envp);

#endif
