/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 01:59:20 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/22 12:34:09 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// returns a dup **s for n, terminates with NULL
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

// returns a dup **s for n, terminates with NULL, frees **s
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

// returns the index of the first occurence of c in s, -1 if none found
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

// prints a char **s, each element on a new line
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
