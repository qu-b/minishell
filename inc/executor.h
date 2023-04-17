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

char	*get_name(t_token **tokens);
char	**get_args(t_token *head);
t_token	*get_last_cmd(t_token *current);


int		set_in_out(t_token **tokens, int *tmpfd);
int		open_infile(t_token *current, int *tmpfd);
int		open_outfile(t_token *current, int *tmpfd);


int		exec_cmd(t_cmd *cmd, t_token *current, t_token *last, int tmpfd);
int		exec_main(t_cmd *cmd, t_token **current, int pid_i, int tmpfd);
int		exec_pipe(t_cmd *cmd, t_token **current, int pid_i);
int		executor(t_token **tokens);

#endif
