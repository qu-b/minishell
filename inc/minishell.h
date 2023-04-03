/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:18:53 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/03 11:12:26 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include "parser.h"
# include "builtins.h"
# include "executor.h"
# include "../lib/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2

# define INFILE 0
# define OUTFILE 1

int		minishell(char **envp);

#endif
