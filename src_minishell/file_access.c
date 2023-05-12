/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaphod <zaphod@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:14:58 by zaphod           #+#    #+#             */
/*   Updated: 2023/04/13 14:41:59 by zaphod          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to print error message
void	print_error(const char *error_type, const char *file_name)
{
	write(STD_ERR, "minishell: ", 11);
	write(STD_ERR, file_name, ft_strlen(file_name));
	write(STD_ERR, ": ", 2);
	write(STD_ERR, error_type, ft_strlen(error_type));
	write(STD_ERR, "\n", 1);
}

// Function to open infile
// changes tmpfd to infile fd and duplicates tmpfd onto STD_IN
int	open_infile(t_token *current, int *tmpfd)
{
	*tmpfd = open(current->next->value, O_RDONLY);
	if (*tmpfd == -1)
	{
		if (errno == ENOENT)
			print_error("No such file or directory", current->next->value);
		else if (errno == EACCES)
			print_error("Permission denied", current->next->value);
		else
			write(STD_ERR, "Error\n", 7);
		return (1);
	}
	close(0);
	dup2(*tmpfd, 0);
	close(*tmpfd);
	return (0);
}

// Function to write/append to outfile
int	open_outfile(t_token *current, int *tmpfd)
{
	if (current->len == 1)
		*tmpfd = open(current->next->value,
				O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else
		*tmpfd = open(current->next->value,
				O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (*tmpfd == -1)
	{
		if (errno == ENOENT)
			print_error("No such file or directory", current->next->value);
		else if (errno == EACCES)
			print_error("Permission denied", current->next->value);
		else
			write(STD_ERR, "Error\n", 7);
		return (1);
	}
	close(1);
	dup2(*tmpfd, 1);
	close(*tmpfd);
	return (0);
}
