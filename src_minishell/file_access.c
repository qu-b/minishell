/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:14:58 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/06 05:41:42 by kpawlows         ###   ########.fr       */
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