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

void	free_cmd(t_cmd *cmd);
void	free_tokens(t_token **tokens);

int		get_n_cmds(t_token *tokens);
char	*get_name(t_token **tokens);
char	**get_args(t_token *head);
t_token	*get_last_cmd(t_token *current);

int		set_in_out(t_token **tokens, t_cmd *cmd, int *tmpfd);
int		open_infile(t_token *current, int *tmpfd);
int		open_outfile(t_token *current, int *tmpfd);

int		exec_cmd(t_cmd *cmd, t_token *current, t_token *last, int tmpfd);
int		exec_main(t_cmd *cmd, t_token **current, int pid_i, int tmpfd);
int		exec_pipe(t_cmd *cmd, t_token **current, int pid_i);
int		executor(void);
int		count_pipes(t_token **tokens);

// adds heredoc functionality to minishell
int		heredoc(t_token **tokens, t_cmd *cmd);
int		heredoc_main(t_token **tokens, t_cmd *cmd);
int		heredoc_find(t_token **tokens, t_cmd *cmd);

char	*define_delimiter(t_token **tokens, int *nldel);

char	**get_words(t_token **tokens, char **del);
char	*cat_words(t_token **tokens, char *all_vals);

char	**read_until_del(char **words, char *del, char *tmp_in, char *tmp_wrd);
void	read_loop(char **tmp_in, char **tmp_wrd, char *del);
int		is_delimiter(char *s, char *del);
int		heredoc_create(t_cmd *cmd, char **words);

int		exec_heredoc(t_cmd *cmd, pid_t pid_i);
int		process_nls(t_token **tokens, char *s, char *del, int idx);
char	*trim_last(char *s, char *del, int i);

char	**get_new_args(t_token **tokens, t_cmd *cmd);
void	manage_tokens(t_token **tokens, char *del, int idx);

// joins NULL terminated ptrs
char	**ft_ptrjoin(char **s1, char **s2);
// split that includes c
char	**ft_split_inc(char const *s, char const c);
// strim that frees s1
char	*ft_strtrim_free(char *s1, char const *set);

#endif
