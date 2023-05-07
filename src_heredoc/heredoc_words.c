/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 16:52:33 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/07 21:40:16 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns words to be written, manages tokens
char	**get_words(t_token **tokens, char **del)
{
	char	**split;
	char	*all_vals;
	char	*tmp;
	int		i;

	all_vals = cat_words(tokens, ft_strdup(""));
	split = ft_split_inc(all_vals, '\n');
	free(all_vals);
	i = -1;
	while (split[++i])
	{
		printf("> %s", split[i]);
		tmp = ft_strtrim(split[i], " \n");
		if (is_delimiter(tmp, *del) == 1)
		{
			split[i] = ft_strtrim_free(split[i], " \n");
			free(split[++i]);
			split[i] = NULL;
			free(tmp);
			break ;
		}
		free(tmp);
	}
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
		all_vals = ft_strjoin_gnl(all_vals, " ");
		head = head->next;
	}
	return (all_vals);
}
