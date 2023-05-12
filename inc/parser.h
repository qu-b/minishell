/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:31:42 by zaphod           #+#    #+#             */
/*   Updated: 2023/05/03 07:52:51 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

int		parser(char *input);

int		expand_home(t_token **current, char **env);
char	*get_variable_value(char *s);
void	ft_append_char(char **buf, char tmp);

// Lexer
int		lexer(t_token **head, char *s);
void	process_tokens(t_token *tokens);

// Utils
void	ft_freeptr(char **s);
int		is_sq(char c);
int		is_dq(char c);
int		is_io(char *s);
int		is_pipe(char c);
int		is_exit(char *s);
int		is_variable(char *s);
int		find_space(char *str);
int		ft_is_builtin(t_cmd *cmd);
void	print_tokens(t_token *head);

// Token Utils
int		str_length(char *s);
t_token	*tokenize_string(char **input);
t_token	*create_token(enum e_token_type type, char *value, int len);
void	del_token(t_token **tokens);

#endif
