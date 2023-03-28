/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:37:50 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/24 22:40:01 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo_find_opt(char **args, int argnb)
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
		if (j == 1 && args[i][0] != '-')
			j++;
		if (j == ft_strlen(args[i]))
			i++;
		else
			break ;
	}
	return (i);
}

void	ft_echo(char **args)
{
	int		i;
	int		argnb;
	int		nl;

	nl = 0;
	argnb = ft_argcount(args);
	if (argnb < 2)
		return ;
	i = 0;
	nl = ft_echo_find_opt(args, argnb);
	i += nl;
	while (++i < argnb)
	{
		ft_printf("%s", args[i]);
		if (i < argnb - 1)
			ft_printf(" ");
	}
	if  (argnb == 2 )
		i = 0;
	if (nl == 0 || (argnb == 2 && args[1][0] == '-'))
		ft_printf("\n");
}