/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:59:20 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/07 21:44:58 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**ft_ptrdup(char **s, int n)
{
	int		i;
	char	**out;

	i = -1;
	out = malloc(sizeof(char *) * (n + 1));
	if (!out)
		return (NULL);
	while (++i < n)
		out[i] = ft_strdup(s[i]);
	out[i] = NULL;
	return (out);
}

char	**ft_ptrdup_free(char **s, int n)
{
	int		i;
	char	**out;

	i = -1;
	out = malloc(sizeof(char *) * (n + 1));
	if (!out)
		return (NULL);
	while (++i < n)
		out[i] = ft_strdup(s[i]);
	out[i] = NULL;
	ft_freeptr(s);
	return (out);
}

int	ft_strchr_idx(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == (char) c)
			return (i);
		i++;
	}
	if (s[i] == (char) c)
		return (i);
	return (-1);
}

void	ft_printptr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_printf("%s\n", s[i]);
		i++;
	}
}
