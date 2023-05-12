/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:00:14 by zaphod           #+#    #+#             */
/*   Updated: 2023/04/12 17:59:52 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freeptr(char **s)
{
	int	i;

	i = -1;
	while (s[++i] != NULL)
		free(s[i]);
	free(s);
}

int	is_sq(char c)
{
	if (c == '\'')
		return (1);
	else
		return (0);
}

int	is_dq(char c)
{
	if (c == '\"')
		return (1);
	else
		return (0);
}

int	is_variable(char *s)
{
	if ((*s == '$' && *(s + 1)) && (ft_isalnum(*(s + 1)) || *(s + 1) == '_'))
		return (1);
	return (0);
}

int	is_exit(char *s)
{
	if ((*s == '$' && *(s + 1)) && *(s + 1) == '?')
		return (1);
	return (0);
}
