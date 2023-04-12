/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:50:23 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/12 18:46:17 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

char 	*get_args_old(t_token **head);
char 	**get_args_ptr(t_token **head);
int		openfile(char *filename, int mode);
char	*find_path(char **envp);
char	*get_cmd(char **paths, char *cmd);
void	exec(char *cmd, char **envp);
void	redirect(char *cmd, char **env, int fdin);
void	exec_pipe(char *cmd, char **env, int fdin, int fdout);
int		executor(t_token *tokens);

#endif
