/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:00:07 by zaphod           #+#    #+#             */
/*   Updated: 2023/05/07 21:53:48 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include "minishell.h"

// Define Token Type
enum	e_token_type
{
	IO,
	PIPE,
	WORD,
};

// Define Token Structure
typedef struct s_token
{
	enum e_token_type	type;
	char				*value;
	int					len;
	struct s_token		*next;
}	t_token;

// Define Command Structure
typedef struct s_cmd
{
	char	*name;
	char	**args;
	int		pipe[2];
	int		tmpfd;
	int		heredoc;
}	t_cmd;

// Define Data Structure
typedef struct s_data
{
	t_token	*tokens;
	char	**env;
	int		ext;
	t_cmd	cmd;
	char	*input;
	pid_t	*pid;
	int		exit_status;
}	t_data;

#endif
