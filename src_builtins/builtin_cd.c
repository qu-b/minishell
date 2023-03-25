/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:32:10 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/24 17:04:11 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_cd(char **args)
{
	DIR *dir;
	(void) args;
	// ft_printf("%s\n", args[1]);
	dir = opendir(args[1]);
	if (!dir)
		return ;
	readdir(dir);
	// ??
	return ;
}
