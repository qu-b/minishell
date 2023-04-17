/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 09:45:49 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/17 11:16:11 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	append_open_file(char *name)
{
	int	fd;

	fd = open(name, O_RDWR | O_APPEND | O_CREAT, 0644);
	// if (fd == -1)
		return (fd);
}

int	append(t_token **tokens, t_cmd *cmd, pid_t pid_i)
{
	int	tmpfd;

	(void) tmpfd;
	(void) cmd;
	(void) pid_i;
	if ((*tokens) && (*tokens)->type == IO && \
	ft_strncmp((*tokens)->value, ">>", 2) == 0)
	{
		(*tokens) = (*tokens)->next;
		if ((*tokens) && (*tokens)->type == WORD)
		{
			tmpfd = append_open_file((*tokens)->value);
			// redirection magic
			return (0);
		}
		else
		{
			write(2, "append error\n", 14);
			return (-1);
		}
	}
	return (0);
}