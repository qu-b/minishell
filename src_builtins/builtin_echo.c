/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:37:50 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/06 15:26:35 by kpawlows         ###   ########.fr       */
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
	printf("i final = %d\n", i);
	while (++i < argnb)
	{
		ft_printf("%s", args[i]);
		if (i < argnb - 1)
			ft_printf(" ");
	}
	if (args[1] == NULL || nl == 0)
		ft_printf("\n");
}
