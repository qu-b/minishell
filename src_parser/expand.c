/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:55:47 by fcullen           #+#    #+#             */
/*   Updated: 2023/04/19 12:30:38 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_home(t_token **current, char **env)
{
	(*current)->value = ft_getenv(env, "HOME");
	if (!(*current)->value)
		(*current)->value = "~";
	return (0);
}

int	expand_exit_status(t_token **current, int status)
{
	(*current)->value = ft_itoa(status);
	return (0);
}