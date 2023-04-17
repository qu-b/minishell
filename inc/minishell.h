/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:18:53 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/13 21:59:01 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <termios.h>
# include <errno.h>
# include "parser.h"
# include "builtins.h"
# include "executor.h"
# include "signals.h"
# include "../lib/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

# define INFILE 0
# define OUTFILE 1

typedef struct s_data
{
	t_token	*tokens;
	char	**env;
	int		ext;
	t_cmd	cmd;
	pid_t	*pid;
}	t_data;

t_data	*g_data;

int		minishell(char **envp);
t_data	*get_data(char **envp);

#endif
