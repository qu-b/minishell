/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:37:50 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/23 15:49:52 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	echo_find_opt(char **args, int argnb)
{
	int		i;
	size_t	j;

	i = 0;
	args++;
	while (i < argnb -1)
	{
		j = 1;
		if (args[i][0] == '-')
		{
			while (args[i][j] && args[i][j] == 'n')
				j++;
		}
		if (j == ft_strlen(args[i]) && j == 1)
			j--;
		if (j == ft_strlen(args[i]))
			i++;
		else
			break ;
	}
	return (i);
}

void	ft_echo(char **args)
{
	int	i;
	int	argnb;
	int	nl;

	nl = 0;
	argnb = ft_argcount(args);
	i = 0;
	nl = echo_find_opt(args, argnb);
	i += nl;
	while (++i < argnb)
	{
		printf("%s", args[i]);
		if (i < argnb - 1)
			printf(" ");
	}
	if (args[1] == NULL || nl == 0)
		printf("\n");
	g_data->exit_status = 0;
}
