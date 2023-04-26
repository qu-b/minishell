/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:55:47 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/26 14:35:21 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_home(t_token **current, char **env)
{
	if ((*current)->value[0] == '~')
		(*current)->value = ft_getenv(env, "HOME");
	return (0);
}

char	*expand_exit_status(char *s, int status)
{
	s = ft_itoa(status);
	return (s);
}
