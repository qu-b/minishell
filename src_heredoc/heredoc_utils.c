/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 21:05:01 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/22 13:48:24 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// looks for delimiter after <<, returns it or null if none found
// sets nldel to 1 if the delimiter is directly followed by a newline
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
		g_data->exit_status = 1;
		return (NULL);
	}
	del = ft_strtrim_free(del, " ");
	return (del);
}

// checks if s is del, returns 1 if true 0 if false
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

// joins two arrays of strings
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

// joins heredoc args (before 1st nl but after delimiter) to existing args
char	**get_new_args(t_token **tokens, t_cmd *cmd)
{
	char	**new_args;
	t_token	*head;
	int		i;

	i = 0;
	head = *tokens;
	while (head && head->type == WORD)
	{
		i++;
		head = head->next;
	}
	new_args = malloc(sizeof(char *) * (i + 3));
	i = 0;
	while ((*tokens) && (*tokens)->type == WORD)
	{
		if (!(*tokens)->value)
			break ;
		new_args[i] = ft_strtrim((*tokens)->value, " ");
		(*tokens) = (*tokens)->next;
		i++;
	}
	new_args[i] = NULL;
	return (ft_ptrjoin(cmd->args, new_args));
}

// checks if "<<" is present in tokens in the current command
// returns index of << token or 0 if not found
int	heredoc_find(t_token **tokens, t_cmd *cmd)
{
	t_token	*tmp;
	int		i;

	(void) cmd;
	tmp = *tokens;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp && tmp->type == IO && ft_strncmp(tmp->value, "<<", 2) == 0)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (0);
}
