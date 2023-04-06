/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 06:38:03 by kpawlows          #+#    #+#             */
/*   Updated: 2023/04/06 09:57:22 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_handle_in(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_redisplay();
		printf("  \b\b");
	}
}

void	sig_handle_ext(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_data->ext = 0;
	}
	if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
		rl_redisplay();
		rl_on_new_line();
		rl_replace_line("", 0);
		g_data->ext = 0;
	}
}

void sig_handle(int sig)
{
	if (g_data->ext == 0)
		sig_handle_in(sig);
	if (g_data->ext == 1)
		sig_handle_ext(sig);
}

void	sig_acccept(void)
{
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, sig_handle);
}
