/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 09:29:03 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/16 09:32:36 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc(t_token **tokens, t_cmd *cmd)
{
	t_token	*head;
	char	*del;

	head = *tokens;
	if (head && head->next && head->next->type == IO && ft_strncmp(head->next->value, "<<", 2) == 0)
	{
		head = del_token(&head->next, &head);
		if (head->next && head->next->type == WORD)
		{
			head = del_token(&head->next, &head);
			del = define_delimiter(&head);
			if (!del)
				return (-1);
			add_to_args(cmd->args, get_del(1, del, head->value));
			return (0);
		}
		else
			write(2, "heredoc error\n", 14);
	}
	return (0);
}

t_token	*del_token(t_token **tokens, t_token **prev)
{	
	(*prev)->next = (*tokens)->next;	
	if ((*tokens))
	{
		free((*tokens)->value);
		free((*tokens));
		// and smth else probably
	}
	return((*prev)->next);
}

char	**add_to_args(char **args, char *s)
{
	char	**out;
	int 	i;

	out = malloc(sizeof(char *) * ft_argcount(args) + 2);
	if (!out)
		return (NULL);
	i = -1;
	while (args[++i])
		out[i] = args[i];
	out[i] = s;
	out[i + 1] = NULL;
	return (out);
}
/*

cat << EOF
heyoohohh
jijiji
klklklkl
plplplplplpl
EOF
hihi

ls | cat -e | cat -e | cat -e | cat -e

*/