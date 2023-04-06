/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:16:24 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/06 05:41:51 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_io(char *s)
{
	if (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">>", 2))
		return (2);
	if (*s == '<' || *s == '>')
		return (1);
	return (0);
}

int	is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	ft_is_builtin(char *cmd)
{
	int	len;
	
	len = builtin_cmd_len(cmd);
	if (ft_strncmp(cmd, "echo", len) == 0 && len == 4)
		return(1);
	else if (ft_strncmp(cmd, "env", len) == 0 && len == 3)
		return(1);
	else if (ft_strncmp(cmd, "pwd", len) == 0 && len == 3)
		return(1);
	else if (ft_strncmp(cmd, "cd", len) == 0 && len == 2)
		return(1);
	else if (ft_strncmp(cmd, "export", len) == 0 && len == 6)
		return(1);
	else if (ft_strncmp(cmd, "unset", len) == 0 && len == 5)
		return(1);
	else if (ft_strncmp(cmd, "exit", len) == 0 && len == 4)
		return(1);
	return (0);
}

void	print_tokens(t_token *head)
{
	while (head)
	{
		printf("Token value: [%s]   Type: [%d]\n", head->value, head->type);
		head = head->next;
	}
}
