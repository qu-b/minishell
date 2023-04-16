/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:05:01 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/16 21:05:03 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*define_delimiter(t_token **tokens)
{
	t_token	*head;
	char	*del;
	int		nl;
	char	*tmp;

	head = *tokens;
	nl = ft_strchr_idx(head->value, '\n');
	if (nl <= 0)
	{
		write(2, "heredoc error\n", 14);
		return (NULL);
	}
	del = ft_substr(head->value, 0, nl);
	tmp = ft_substr(head->value, nl + 1, ft_strlen(head->value) - nl);
	free(head->value);
	head->value = tmp;
	// head->value += nl;
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
