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
	int		heredoc;
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
int		count_pipes(t_token **tokens);


// adds heredoc functionality to minishell
int		heredoc(t_token **tokens, t_cmd *cmd, pid_t pid_i);
int		find_heredoc(t_token **tokens, t_cmd *cmd, pid_t pid_i);

// returns the delimiter or NULL if none found
// trims the token val if something remains after delimiter (for **args)
// sets nldel to 1 if delimiter is \n
char	*define_delimiter(t_token **tokens, int *nldel);

// joins WORD token values until one is a delimiter
// returns them as a string, adding \n in between tokens
// advances tokens
char	**get_words(t_token **tokens, char **del);

// if no del exists in words, readlines until a del is found
// returns words joined with del
char	**read_until_del(char **words, char *del, char *tmp_in, char *tmp_wrd);
void	read_loop(char **tmp_in, char **tmp_wrd, char *del);
// returns 0 if s is delimiter, -1 if not
int		is_delimiter(char *s, char *del);
// creates /tmp/mini_heredoc file, writes **words to it
int		heredoc_create_file(char **words);
// executes the heredoc with the given command
int		exec_heredoc(t_cmd *cmd, pid_t pid_i);
// gets heredoc args
char	**get_new_args(t_token **tokens, char *s);

// appends
int	append(t_token **tokens, t_cmd *cmd, pid_t pid_i);
// opens a file in append mode
int		open_file_append(char *name);

// joins NULL terminated ptrs
char	**ft_ptrjoin(char **s1, char **s2);
// split that includes c
char	**ft_split_inc(char const *s, char const c);
// strim that frees s1
char	*ft_strtrim_free(char *s1, char const *set);


#endif
