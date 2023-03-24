/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:16:24 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/24 15:29:29 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

int	is_io(char *s)
{
	if (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">>", 2))
		return (2);
	if (*s == '<' || *s == '>')
		return (1);
	return (0);
}

int is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	ft_is_builtin(char *command)
{
	static const char	*valid_builtins[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit", NULL};
	int					i;

	i = 0;
	while (valid_builtins[i])
	{
		if (ft_strncmp(valid_builtins[i], command, ft_strlen(command)))
			return (1);
	}
	return (0);
}
