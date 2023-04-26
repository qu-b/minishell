/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:00:14 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/12 17:59:52 by fcullen          ###   ########.fr       */
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
