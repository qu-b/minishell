/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:14:58 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/13 14:41:59 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	openfile(char *filename, int mode)
{
	if (mode == INFILE)
	{
		if (access(filename, F_OK))
		{
			write(STD_ERR, "minishell: ", 11);
			write(STD_ERR, filename, ft_strlen(filename));
			write(STD_ERR, ": No such file or directory\n", 28);
			return (0);
		}
		if (access(filename, R_OK))
		{
			write(STD_ERR, "minishell: ", 11);
			write(STD_ERR, filename, ft_strlen(filename));
			write(STD_ERR, ": Permission denied\n", 20);
			return (0);
		}
		else
			return (open(filename, O_RDONLY));
	}
	else
		return (open(filename, O_TRUNC | O_CREAT | O_RDWR, 0000644));
}

// parse_cmd()
// if (head->type == IO && head->len == 1)
// 		{
// 			if (head->value[0] == '<')
// 				fdin = openfile(head->next->value, 0);
// 			else
// 				fdout = openfile(head->next->value, 1);
// 		}