/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_inc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:17:52 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/17 09:25:48 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_issep(char const *s, char c, int i)
{
	if (s[i] == c && s[i] != '\0')
		i++;
	return (i);
}

int	ft_isword(char const *s, char c, int i)
{
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		i = ft_isword(s, c, i);
		while (s[i] && (s[i++] == c || s[i] == '\0'))
			count++;
	}
	return (count);
}

char	**ft_split_inc(char const *s, char const c)
{
	int		i;
	int		j;
	int		wc;
	char	**split;

	i = 0;
	j = 0;
	wc = ft_wordcount(s, c);
	split = malloc(sizeof(char *) * wc + sizeof(char *));
	if (split == NULL)
		return (NULL);
	while (i < wc)
	{
		if (i != 0)
			j = ft_issep(s, c, j);
		split[i] = malloc(sizeof(char) * ft_isword(s, c, j) - j + 1);
		ft_strlcpy(split[i], &s[j], ft_isword(s, c, j) - j + 2);
		j = ft_isword(s, c, j);
		i++;
	}
	split[i] = NULL;
	return (split);
}

char	*ft_strtrim_free(char *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*trim;

	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	while (end > start)
	{
		if (!ft_strrchr(set, s1[end - 1]))
			break ;
		end--;
	}
	trim = malloc(sizeof(char) * (end - start + 1));
	if (!trim)
		return (0);
	i = 0;
	while (start < end && s1[start])
		trim[i++] = s1[start++];
	trim[i] = 0;
	free(s1);
	return (trim);
}
