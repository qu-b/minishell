/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 06:38:03 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/06 05:41:48 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_handle(int sig)
{
	if (sig == SIGINT) // && is parent process
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_redisplay();
	}
}

void	sig_acccept(void)
{
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, sig_handle);
}