/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:50:23 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/14 13:44:26 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

typedef struct s_cmd
{
	char	*name;
	char	**args;
	int		pipe[2];
	int		tmpfd;
}	t_cmd;

char 	**get_args(t_token **head);
int		openfile(char *filename, int mode);
char	*find_path(char **envp);
char	*get_cmd(char **paths, char *cmd);
void	exec(t_cmd *cmd, char **envp);
int		exec_bin(t_cmd *cmd, char **env, int pid_i, int tmpfd);
int		exec_pipe(t_cmd *cmd, char **env, int pid_i);
int		executor(t_token **tokens);
int		count_pipes(t_token **tokens);

int		heredoc(t_token **tokens, t_cmd *cmd, pid_t pid_i);
int		exec_heredoc(t_cmd *cmd, pid_t pid_i, char *doc);
char	*delimit(char *s, char *del);
int		find_delimiter(char *s, char *del);
char	*define_delimiter(t_token **tokens);
void	del_token(t_token **tokens);
char	**add_to_args(char **args, char *s);

#endif
