/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:05:01 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/16 22:47:41 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_delimiter(t_token **tokens, char **del, char **out)
{
	int		delpos;
	char	*stmp;
	char	*stmp2;

	delpos = find_delimiter(*out, *del);
	if (delpos >= 0)
	{
		stmp = ft_substr((*tokens)->value, 0, delpos);
		stmp2 = (*tokens)->value;
		*out = ft_strjoin_gnl(*out, stmp);
		delpos = find_delimiter(stmp, *del) + ft_strlen(*del) + 1;
		(*tokens)->value = ft_substr((*tokens)->value, delpos, \
		ft_strlen((*tokens)->value) - delpos);
		free(stmp);
		free(stmp2);
		return (1);
	}
	return (0);
}

char	*get_word_string(t_token **tokens, char **del)
{
	char	*out;
	t_token	*ttmp;

	out = ft_strdup("");
	while ((*tokens) && (*tokens)->value && (*tokens)->type == WORD)
	{
		out = ft_strjoin_gnl(out, (*tokens)->value);
		if (!(*del))
			*del = define_delimiter(&out);
		ttmp = (*tokens);
		if (get_delimiter(tokens, del, &out))
			break ;
		(*tokens) = (*tokens)->next;
		del_token(&ttmp);
	}
	return (out);
}

char	*define_delimiter(char **words)
{
	char	*del;
	int		nl;
	char	*tmp;

	nl = ft_strchr_idx(*words, '\n');
	if (nl <= 0)
		return (NULL);
	del = ft_substr(*words, 0, nl);
	tmp = ft_substr(*words, nl + 1, ft_strlen(*words) - nl);
	free(*words);
	*words = tmp;
	return (del);
}

int	find_delimiter(char *s, char *del)
{
	int	i;
	int	dlen;
	int	slen;

	if (!del)
		return (-1);
	dlen = ft_strlen(del);
	slen = ft_strlen(s);
	i = -1;
	while (s[++i] && i < slen - dlen + 1)
	{
		if (ft_strncmp(&s[i], del, dlen) == 0)
			return (i);
	}
	return (-1);
}

char	*delimit(char *s, char *del)
{
	char	*out;
	int		delpos;

	if(!s || !del)
		return (NULL);
	delpos = 0;
	delpos = find_delimiter(s, del);
	if (delpos == -1)
		return (NULL);
	out = ft_substr(s, 0, delpos);
	// out[delpos] = 0x00;
	return (out);
}
