/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:51:35 by fcullen           #+#    #+#             */
/*   Updated: 2023/03/28 16:43:20 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_space(char *s)
{
	int	i;

	i = 0;
	while (!is_pipe(*s) || !is_io(s))
	{
		if (s[i] == ' ' || s[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	str_length(char *s)
{
	int	i;
	int	insq;
	int	indq;

	i = 0;
	insq = 0;
	indq = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !insq && !indq)
			insq = 1;
		else if (s[i] == '\'' && insq && !indq)
			insq = 0;
		if ((s[i] == '"') && !indq && !insq)
			indq = 1;
		else if (s[i] == '"' && indq && !insq)
			indq = 0;
		if (s[i] == ' ' && !indq && !insq)
			return (i + 1);
		if ((is_io(s + i) || is_pipe(*(s + i))) && !insq && !indq)
			return (i);
		i++;
	}
	return ((insq || indq) * (-1) + (!(insq || indq)) * i);
}