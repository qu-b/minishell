/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:52:33 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/21 17:04:23 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns words to be written, manages tokens
char	**get_words(t_token **tokens, char **del)
{
	char	**split;
	char	*all_vals;
	int		i;

	all_vals = cat_words(tokens, ft_strdup(""));
	split = ft_split_inc(all_vals, '\n');
	free(all_vals);
	i = -1;
	while (split[++i])
	{
		ft_printf("> %s", split[i]);
		if (ft_strncmp(split[i], *del, ft_strlen(*del)) == 0)
		{
			split[i] = ft_strtrim_free(split[i], "\n");
			free(split[++i]);
			split[i] = NULL;
			break ;
		}
	}
	manage_tokens(tokens, *del, i - 1);
	return (split);
}

// returns a string with WORD type tokens concatenated, until non-WORD token
char	*cat_words(t_token **tokens, char *all_vals)
{
	t_token	*head;

	head = *tokens;
	while (head && head->value && head->type == WORD)
	{
		all_vals = ft_strjoin_gnl(all_vals, head->value);
		all_vals = ft_strjoin(all_vals, " ");
		head = head->next;
	}
	return (all_vals);
}

// returns the number of newlines in s until del is found
int	count_nl_del(char *s, char *del)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			n++;
		i++;
		if (ft_strncmp(&s[i], del, ft_strlen(del)) == 0)
			break ;
	}
	return (n);
}

// trims last token after del, if such exists
char *trim_last(char *s, char *del, int i)
{
	int 	nl_idx;
	int		nl_count;
	char	*out;

	if (!s || !del)
		return (NULL);
	nl_idx = 0;
	nl_count = count_nl_del(s, del);
	while (s[i] && nl_idx <= nl_count)
	{
		if (s[i] == '\n')
			nl_idx++;
		i++;
	}
	out = ft_substr(s, i, ft_strlen(&s[i]));
	return (out);
}

// cleans up tokens for anything after heredoc
void	manage_tokens(t_token **tokens, char *del, int idx)
{
	t_token	*tmp;
	int		count;
	int		tidx;

	tmp = *tokens;
	count = 0;
	tidx = 0;
	while (tmp)
	{
		count += count_nl_del(tmp->value, del);
		if (count >= idx)
			break ;
		tmp = tmp->next;
		tidx++;
	}
	while (tidx--)
		(*tokens) = (*tokens)->next;
	(*tokens)->value = trim_last((*tokens)->value, del, 0);
}
