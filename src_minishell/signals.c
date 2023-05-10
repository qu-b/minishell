/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 06:38:03 by kpawlows          #+#    #+#             */
/*   Updated: 2023/05/10 23:57:20 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	show_ctrl_disable(void)
{
	struct termios	term;

	tcgetattr(STD_IN, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STD_IN, TCSANOW, &term);
}

void	show_ctrl_enable(void)
{
	struct termios	term;

	tcgetattr(STD_IN, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STD_IN, TCSANOW, &term);
}

void	sig_handle(int sig)
{
	if (g_data->ext == 0)
	{
		if (sig == SIGINT)
		{
			printf("\n");
			rl_replace_line("", 0);
		}
		rl_on_new_line();
		rl_redisplay();
	}
	if (g_data->ext == 1)
	{
		if (sig == SIGINT)
			printf("\n");
		if (sig == SIGQUIT)
		{
			printf("Quit: 3\n");
			rl_redisplay();
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		g_data->ext = 0;
	}
}

void	sig_acccept(void)
{
	show_ctrl_disable();
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, sig_handle);
}
