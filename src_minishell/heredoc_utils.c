/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:05:01 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/17 09:28:38 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_words(t_token **tokens, char **del)
{
	char	**split;
	char	*all_vals;
	int		i;

	i = 0;
	all_vals = ft_strdup("");
	while ((*tokens) && (*tokens)->value && (*tokens)->type == WORD)
	{
		all_vals = ft_strjoin_gnl(all_vals, (*tokens)->value);
		(*tokens) = (*tokens)->next;
	}
	split = ft_split_inc(all_vals, '\n');
	free(all_vals);
	i = -1;
	while (split[++i])
	{
		ft_printf("> %s", split[i]);
		if (ft_strncmp(split[i], *del, ft_strlen(*del)) == 0)
		{
			split[i] = ft_strtrim_free(split[i], "\n");
			i++;
			free(split[i]);
			split[i] = NULL;
			break ;
		}
	}
	return (split);
}

char	*define_delimiter(t_token **tokens, int *nldel)
{
	char	*del;
	char	*tmp;
	int		nl;

	nl = ft_strchr_idx((*tokens)->value, '\n');
	if (nl >= 0)
		*nldel = 1;
	else
		nl = ft_strlen((*tokens)->value);
	del = ft_substr((*tokens)->value, 0, nl);
	tmp = ft_substr((*tokens)->value, nl + 1, ft_strlen((*tokens)->value) - nl);
	free((*tokens)->value);
	(*tokens)->value = tmp;
	if (!tmp || !tmp[0])
		(*tokens) = (*tokens)->next;
	if (!del)
	{
		write(2, "heredoc error\n", 14);
		return (NULL);
	}
	del = ft_strtrim_free(del, " ");
	return (del);
}

int	is_delimiter(char *s, char *del)
{
	int	dlen;
	int	slen;

	if (!del)
		return (0);
	dlen = ft_strlen(del);
	slen = ft_strlen(s);
	if (slen != dlen)
		return (0);
	if (ft_strncmp(s, del, dlen) == 0)
		return (1);
	return (0);
}

char	**ft_ptrjoin(char **s1, char **s2)
{
	char	**new;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	new = malloc(sizeof(char *) * (ft_argcount(s1) + ft_argcount(s2) + 2));
	if (!new)
		return (NULL);
	while (s1[++i])
		new[i] = ft_strdup(s1[i]);
	while (s2[++j])
		new[i + j] = ft_strdup(s2[j]);
	new[i + j] = NULL;
	ft_freeptr(s1);
	ft_freeptr(s2);
	return (new);
}
