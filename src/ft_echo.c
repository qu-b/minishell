/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:37:50 by kpawlows          #+#    #+#             */
/*   Updated: 2023/03/22 23:48:49 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../inc/minishell.h"
#include "../inc/builtins.h"

int	ft_argcount(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

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

	argnb = ft_argcount(args);
	if (argnb < 2)
		return ;
	i = 0;
	nl = ft_echo_find_opt(args, argnb);
	i += nl;
	while (++i < argnb)
	{
		ft_printf("%s", args[i]);
		if (i != argnb - 1)
			ft_printf(" ");
	}
	if (nl == 0)
		ft_printf("\n");
}

// void	test_ft_echo(int argc, char **argv)
// {
// 	char	**args;
// 	int		i;

// 	i = 0;
// 	args = malloc(sizeof(char *) * (argc + 2));
// 	args[0] = ft_strdup("echo");
// 	while (++i < argc)
// 		args[i] = ft_strdup(argv[i]);
// 	args[i] = NULL;
// 	ft_echo(args);
// 	i = -1;
// 	while (++i < argc)
// 		free(args[i]);
// 	free(args);
// }
