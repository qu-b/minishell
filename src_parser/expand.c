/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:55:47 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/24 18:38:11 by fcullen          ###   ########.fr       */
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